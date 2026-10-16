import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/multitracks_import_job.dart';
import '../models/multitracks_origin.dart';
import '../models/multitracks_song_details.dart';
import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../providers/multitracks_provider.dart';
import '../services/multitracks_content_provider.dart';
import '../services/multitracks_contract.dart';
import '../services/multitracks_import_coordinator.dart';
import '../services/track_navigation.dart';
import '../theme/app_colors.dart';
import '../widgets/multitracks_import_progress.dart';

/// Id local de uma música MultiTracks (o mesmo que o importador gera): mesma música e tonalidade = mesma Track.
String multitracksTrackId(int contentId, int keyId) =>
    'multitracks-$contentId-$keyId';

/// O Playback abre uma música da biblioteca usando o próprio `songID` como `contentID`. O tipo 26 identifica o
/// produto MultiTrack/AppTrack e `keyID: 0` pede apenas os metadados; a tonalidade real é resolvida da resposta antes
/// de qualquer pedido de link.
MultiTracksContentSelection multitracksSelectionForLibrarySong(
  MultiTracksSongSummary summary,
) => MultiTracksContentSelection(
  contentId: summary.songId,
  contentType: 26,
  keyId: 0,
);

/// Detalhes, tonalidade, faixas e direito de uma música; daqui sai o download. Abrir esta tela só consulta metadados
/// (`downloadLink: false`, `redeemRental: false`).
///
/// [summary] vem da biblioteca; [selection] identifica o conteúdo em `content/download`. Quando só [summary] é
/// informado, a tela usa o vínculo observado no Playback e resolve a tonalidade original com a resposta de metadados.
class MultiTracksSongScreen extends ConsumerStatefulWidget {
  final MultiTracksSongSummary? summary;
  final MultiTracksContentSelection? selection;

  /// Aberta a partir de "Adicionar música": ao concluir, devolve a [Track] em vez de abrir a performance.
  final bool pickMode;

  const MultiTracksSongScreen({
    super.key,
    this.summary,
    this.selection,
    this.pickMode = false,
  }) : assert(summary != null || selection != null);

  @override
  ConsumerState<MultiTracksSongScreen> createState() =>
      _MultiTracksSongScreenState();
}

class _MultiTracksSongScreenState extends ConsumerState<MultiTracksSongScreen> {
  MultiTracksContentSelection? _selection;
  MultiTracksSongDetails? _details;
  String? _error;
  bool _loading = false;
  int _token = 0;

  @override
  void initState() {
    super.initState();
    _selection =
        widget.selection ??
        (widget.summary == null
            ? null
            : multitracksSelectionForLibrarySong(widget.summary!));
    if (_selection != null) Future.microtask(() => _consult(_selection!));
  }

  Future<void> _consult(MultiTracksContentSelection selection) async {
    final token = ++_token;
    final generation = ref.read(multitracksSessionProvider).generation;
    setState(() {
      _selection = selection;
      _loading = true;
      _error = null;
    });
    String? error;
    MultiTracksSongDetails? details;
    try {
      final response = await ref
          .read(multitracksContentProvider)
          .consultMetadata(selection);
      if (!response.isSuccess) {
        error =
            'A MultiTracks recusou a consulta (resultado ${response.result}, erro ${response.errorCode}).';
      } else {
        details = MultiTracksSongDetails.from(
          selection,
          response,
          summary: widget.summary,
        );
        if (selection.keyId == 0) {
          final resolved = details.resolvedSelection;
          if (resolved == null) {
            error =
                'A resposta não informou uma tonalidade disponível para esta música.';
            details = null;
          } else {
            details = MultiTracksSongDetails.from(
              resolved,
              response,
              summary: widget.summary,
            );
            selection = resolved;
          }
        }
      }
    } on MultiTracksStaleSession {
      error = 'A sessão MultiTracks mudou. Volte e abra a música de novo.';
    } on MultiTracksHttpFailure catch (failure) {
      if (failure.statusCode == 401 || failure.statusCode == 403) {
        await ref
            .read(multitracksSessionProvider.notifier)
            .markExpired(generation);
        error = 'A sessão MultiTracks expirou. Entre novamente.';
      } else {
        error = 'O servidor respondeu HTTP ${failure.statusCode}.';
      }
    } on FormatException {
      error = 'Metadados em formato inesperado.';
    } on Object {
      error = 'Sem conexão com a MultiTracks. Tente novamente.';
    }
    if (!mounted || token != _token) return;
    setState(() {
      _selection = details?.selection ?? selection;
      _loading = false;
      _error = error;
      _details = details;
    });
  }

  void _selectKey(int keyId) {
    final current = _selection;
    if (current == null || current.keyId == keyId) return;
    _consult(
      MultiTracksContentSelection(
        contentId: current.contentId,
        contentType: current.contentType,
        keyId: keyId,
        midiBankId: current.midiBankId,
        demoSetlistSongId: current.demoSetlistSongId,
      ),
    );
  }

  Future<void> _enterIdentifier() async {
    final selection = await showContentIdentifierDialog(context);
    if (selection != null && mounted) await _consult(selection);
  }

  Future<void> _download() async {
    final details = _details;
    if (details == null) return;
    await ref
        .read(multitracksImportProvider.notifier)
        .start(
          MultiTracksImportRequest(
            details,
            libraryId: widget.summary?.libraryId,
          ),
          confirmRental: _confirmRental,
        );
  }

  Future<bool> _confirmRental(MultiTracksRentalPrompt prompt) async {
    if (!mounted) return false;
    final confirmed = await showDialog<bool>(
      context: context,
      barrierDismissible: false,
      builder: (_) => MultiTracksRentalDialog(prompt: prompt),
    );
    return confirmed == true;
  }

  Future<void> _open(Track track) async {
    final saved =
        ref
            .read(trackLibraryProvider)
            .where((t) => t.id == track.id)
            .firstOrNull ??
        track;
    if (widget.pickMode) {
      Navigator.of(context).pop(saved);
    } else {
      await openTrack(context, ref, saved);
    }
  }

  Future<void> _addToSetlist(Track track) async {
    final session = ref.read(setlistSessionProvider);
    if (session == null) return;
    final added = await ref
        .read(setlistSessionProvider.notifier)
        .insertTrack(session.setlist.tracks.length, track);
    if (!mounted) return;
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        content: Text(
          added
              ? 'Adicionada ao fim da setlist "${session.setlist.name}".'
              : 'A música já está na setlist.',
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    final details = _details;
    final summary = widget.summary;
    final selection = _selection;
    final title = details?.title ?? summary?.song ?? 'Música MultiTracks';

    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: Text(title, overflow: TextOverflow.ellipsis),
      ),
      body: SafeArea(
        child: Column(
          children: [
            Expanded(
              child: ListView(
                padding: const EdgeInsets.all(16),
                children: [
                  _Header(details: details, summary: summary),
                  const SizedBox(height: 16),
                  if (selection == null)
                    _PendingIdentity(onEnter: _enterIdentifier),
                  if (_loading)
                    const Padding(
                      padding: EdgeInsets.all(24),
                      child: Center(child: CircularProgressIndicator()),
                    ),
                  if (_error != null)
                    _Notice(
                      icon: Icons.error_outline,
                      color: Colors.redAccent,
                      text: _error!,
                      action: selection == null
                          ? null
                          : TextButton(
                              onPressed: () => _consult(selection),
                              child: const Text('Tentar de novo'),
                            ),
                    ),
                  if (details != null && !_loading) ..._detailsSection(details),
                ],
              ),
            ),
            if (details != null && !_loading) _actionBar(details),
          ],
        ),
      ),
    );
  }

  List<Widget> _detailsSection(MultiTracksSongDetails details) {
    final stems = details.stemsForSelectedKey;
    final job =
        ref.watch(multitracksImportProvider)[MultiTracksImportJob.keyFor(
          details.selection.contentId,
          details.selection.keyId,
        )];
    final busy = job != null && job.phase.isActive;
    final local = ref.watch(trackLibraryProvider);
    final otherKey = local
        .where(
          (t) =>
              t.origin?.contentId == details.selection.contentId &&
              t.origin?.keyId != details.selection.keyId,
        )
        .firstOrNull;
    final expiry = details.entitlement.expiresAt;
    return [
      _SectionTitle('Direito'),
      Wrap(
        spacing: 8,
        runSpacing: 8,
        crossAxisAlignment: WrapCrossAlignment.center,
        children: [
          _Chip(
            details.entitlement.kind.label,
            details.entitlement.kind == MultiTracksEntitlementKind.unknown
                ? kTextDim
                : kAccent,
          ),
          if (expiry != null)
            Text(
              'Válido até ${_formatDate(expiry)}',
              style: const TextStyle(color: kTextDim),
            ),
          if (details.rentalsRemaining != null)
            Text(
              'Créditos de aluguel: ${details.rentalsRemaining}',
              style: const TextStyle(color: kTextDim),
            ),
        ],
      ),
      if (expiry != null && !DateTime.now().toUtc().isBefore(expiry))
        const _Notice(
          icon: Icons.schedule,
          color: Colors.orangeAccent,
          text:
              'A validade informada já passou. O servidor decide se o download ainda é permitido.',
        ),
      const SizedBox(height: 16),
      _SectionTitle('Tonalidade'),
      if (details.keys.isEmpty)
        const Text(
          'A resposta não listou tonalidades; será usada a pedida.',
          style: TextStyle(color: kTextDim),
        )
      else
        Wrap(
          spacing: 8,
          runSpacing: 8,
          children: [
            for (final key in details.keys)
              ChoiceChip(
                label: Text(key.title),
                selected: key.keyId == details.selection.keyId,
                onSelected: busy ? null : (_) => _selectKey(key.keyId),
              ),
          ],
        ),
      if (otherKey != null)
        _Notice(
          icon: Icons.info_outline,
          color: kTextDim,
          text:
              'A tonalidade ${otherKey.key ?? 'outra'} já está no WTracks. Esta será salva como variante separada.',
        ),
      const SizedBox(height: 16),
      _SectionTitle('Faixas (${stems.length})'),
      if (stems.isEmpty)
        const Text(
          'Nenhuma faixa listada para esta tonalidade.',
          style: TextStyle(color: kTextDim),
        )
      else
        for (final (index, stem) in stems.indexed)
          ListTile(
            dense: true,
            contentPadding: EdgeInsets.zero,
            leading: Text(
              '${index + 1}'.padLeft(2, '0'),
              style: const TextStyle(color: kTextDim),
            ),
            title: Text(stem.part, style: const TextStyle(color: kText)),
            subtitle: stem.abbreviation.isEmpty
                ? null
                : Text(
                    stem.abbreviation,
                    style: const TextStyle(color: kTextDim),
                  ),
            trailing: Wrap(
              spacing: 6,
              children: [
                if (stem.clickOrGuide)
                  const _Chip('Click/Guia', Color(0xFFFFC107)),
                if (stem.vocal) const _Chip('Vocal', kTextDim),
              ],
            ),
          ),
      const SizedBox(height: 8),
      const Text(
        'Todas as faixas da tonalidade são importadas. O pacote é convertido de AAC para WAV, que ocupa cerca de 10 vezes '
        'mais espaço (estimativa); o espaço livre é conferido assim que o tamanho real do pacote é conhecido.',
        style: TextStyle(color: kTextDim, fontSize: 12),
      ),
    ];
  }

  Widget _actionBar(MultiTracksSongDetails details) {
    final selection = details.selection;
    final key = MultiTracksImportJob.keyFor(
      selection.contentId,
      selection.keyId,
    );
    final job = ref.watch(multitracksImportProvider)[key];
    final local = ref
        .watch(trackLibraryProvider)
        .where(
          (t) =>
              t.id == multitracksTrackId(selection.contentId, selection.keyId),
        )
        .firstOrNull;
    final hasSetlist = ref.watch(setlistSessionProvider) != null;
    final stems = details.stemsForSelectedKey;
    final validKey =
        details.keys.isEmpty ||
        details.keys.any((k) => k.keyId == selection.keyId);
    final canDownload = stems.isNotEmpty && validKey;
    final notifier = ref.read(multitracksImportProvider.notifier);
    final rentalLabel =
        details.entitlement.kind == MultiTracksEntitlementKind.unknown &&
        details.rentalPossible;

    Widget content;
    if (job != null) {
      content = MultiTracksImportProgress(
        job: job,
        onCancel: () => notifier.cancel(key),
        onRetry: () {
          notifier.dismiss(key);
          _download();
        },
        onDismiss: () => notifier.dismiss(key),
        onOpen: job.track == null ? null : () => _open(job.track!),
        onAddToSetlist: job.track == null || widget.pickMode || !hasSetlist
            ? null
            : () => _addToSetlist(job.track!),
        openLabel: widget.pickMode ? 'Adicionar' : 'Abrir música',
      );
    } else if (local != null) {
      content = Row(
        children: [
          Expanded(
            child: OutlinedButton(
              key: const Key('multitracks-redownload'),
              onPressed: canDownload ? _download : null,
              child: const Text('Baixar novamente'),
            ),
          ),
          const SizedBox(width: 12),
          Expanded(
            child: FilledButton.icon(
              key: const Key('multitracks-open-local'),
              onPressed: () => _open(local),
              icon: const Icon(Icons.play_arrow),
              label: Text(widget.pickMode ? 'Adicionar' : 'Abrir'),
            ),
          ),
        ],
      );
    } else {
      content = FilledButton.icon(
        key: const Key('multitracks-download'),
        onPressed: canDownload ? _download : null,
        style: FilledButton.styleFrom(minimumSize: const Size.fromHeight(48)),
        icon: const Icon(Icons.download),
        label: Text(rentalLabel ? 'Alugar e baixar' : 'Baixar'),
      );
    }
    return Container(
      padding: const EdgeInsets.fromLTRB(16, 12, 16, 16),
      decoration: const BoxDecoration(
        color: kBg,
        border: Border(top: BorderSide(color: kBorder)),
      ),
      child: content,
    );
  }
}

/// Confirmação obrigatória antes de `redeemRental`. Nenhum botão vem focado/preselecionado.
class MultiTracksRentalDialog extends StatefulWidget {
  final MultiTracksRentalPrompt prompt;
  const MultiTracksRentalDialog({super.key, required this.prompt});

  @override
  State<MultiTracksRentalDialog> createState() =>
      _MultiTracksRentalDialogState();
}

class _MultiTracksRentalDialogState extends State<MultiTracksRentalDialog> {
  bool _answered = false;

  void _answer(bool value) {
    if (_answered) return; // bloqueia toques repetidos
    _answered = true;
    Navigator.of(context).pop(value);
  }

  @override
  Widget build(BuildContext context) {
    final prompt = widget.prompt;
    return AlertDialog(
      backgroundColor: kPanelBg,
      title: const Text('Confirmar aluguel', style: TextStyle(color: kText)),
      content: Column(
        mainAxisSize: MainAxisSize.min,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            prompt.keyTitle == null
                ? prompt.title
                : '${prompt.title} — tom ${prompt.keyTitle}',
            style: const TextStyle(color: kText, fontWeight: FontWeight.w600),
          ),
          const SizedBox(height: 12),
          const Text(
            'A conta não tem download liberado para esta música. Confirmar pede um aluguel à MultiTracks e pode consumir '
            'um crédito de Rental da sua organização. O pedido não é repetido automaticamente.',
            style: TextStyle(color: kText),
          ),
          if (prompt.rentalsRemaining != null) ...[
            const SizedBox(height: 8),
            Text(
              'Créditos restantes informados: ${prompt.rentalsRemaining}',
              style: const TextStyle(color: kTextDim),
            ),
          ],
          if (prompt.expiresAt != null) ...[
            const SizedBox(height: 4),
            Text(
              'Validade informada: ${_formatDate(prompt.expiresAt!)}',
              style: const TextStyle(color: kTextDim),
            ),
          ],
        ],
      ),
      actions: [
        TextButton(
          key: const Key('multitracks-rental-cancel'),
          onPressed: () => _answer(false),
          child: const Text('Cancelar'),
        ),
        FilledButton(
          key: const Key('multitracks-rental-confirm'),
          onPressed: () => _answer(true),
          child: const Text('Confirmar aluguel'),
        ),
      ],
    );
  }
}

/// Identificação manual do conteúdo (como na probe), enquanto o vínculo biblioteca→conteúdo não é capturado.
/// Só consulta metadados; nada é baixado ou alugado sem outra ação explícita.
Future<MultiTracksContentSelection?> showContentIdentifierDialog(
  BuildContext context,
) {
  return showDialog<MultiTracksContentSelection>(
    context: context,
    builder: (_) => const _IdentifierDialog(),
  );
}

class _IdentifierDialog extends StatefulWidget {
  const _IdentifierDialog();
  @override
  State<_IdentifierDialog> createState() => _IdentifierDialogState();
}

class _IdentifierDialogState extends State<_IdentifierDialog> {
  final _content = TextEditingController(),
      _type = TextEditingController(),
      _key = TextEditingController();

  @override
  void dispose() {
    _content.dispose();
    _type.dispose();
    _key.dispose();
    super.dispose();
  }

  MultiTracksContentSelection? get _value {
    final content = int.tryParse(_content.text),
        type = int.tryParse(_type.text),
        key = int.tryParse(_key.text);
    if (content == null ||
        type == null ||
        key == null ||
        content <= 0 ||
        type <= 0 ||
        key <= 0) {
      return null;
    }
    return MultiTracksContentSelection(
      contentId: content,
      contentType: type,
      keyId: key,
    );
  }

  @override
  Widget build(BuildContext context) {
    Widget field(String label, TextEditingController controller, Key key) =>
        Padding(
          padding: const EdgeInsets.only(bottom: 8),
          child: TextField(
            key: key,
            controller: controller,
            keyboardType: TextInputType.number,
            inputFormatters: [FilteringTextInputFormatter.digitsOnly],
            decoration: InputDecoration(labelText: label),
            onChanged: (_) => setState(() {}),
          ),
        );
    return AlertDialog(
      title: const Text('Identificador de conteúdo'),
      content: SingleChildScrollView(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            const Text(
              'Experimental: informe os números usados por content/download. Abrir só consulta os metadados.',
              style: TextStyle(fontSize: 13),
            ),
            const SizedBox(height: 8),
            field('contentID', _content, const Key('mt-id-content')),
            field('contentType', _type, const Key('mt-id-type')),
            field('keyID', _key, const Key('mt-id-key')),
          ],
        ),
      ),
      actions: [
        TextButton(
          onPressed: () => Navigator.pop(context),
          child: const Text('Cancelar'),
        ),
        FilledButton(
          key: const Key('mt-id-submit'),
          onPressed: _value == null
              ? null
              : () => Navigator.pop(context, _value),
          child: const Text('Consultar'),
        ),
      ],
    );
  }
}

class _Header extends StatelessWidget {
  final MultiTracksSongDetails? details;
  final MultiTracksSongSummary? summary;
  const _Header({required this.details, required this.summary});

  @override
  Widget build(BuildContext context) {
    final image = details?.imageUrl ?? summary?.image;
    final lines = <String>[
      if ((details?.artist ?? summary?.artist) case final artist?
          when artist.isNotEmpty)
        artist,
      if ((details?.album ?? summary?.album) case final album?
          when album.isNotEmpty)
        album,
    ];
    final facts = <String>[
      if (details?.bpm case final bpm?)
        '${bpm % 1 == 0 ? bpm.toInt() : bpm} BPM',
      if (details?.originalKey case final key?) 'Tom original $key',
    ];
    return Row(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        MultiTracksCover(url: image, size: 96),
        const SizedBox(width: 16),
        Expanded(
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                details?.title ?? summary?.song ?? 'Música MultiTracks',
                style: const TextStyle(
                  color: kText,
                  fontSize: 20,
                  fontWeight: FontWeight.w600,
                ),
              ),
              for (final line in lines)
                Text(line, style: const TextStyle(color: kTextDim)),
              if (facts.isNotEmpty) ...[
                const SizedBox(height: 6),
                Wrap(
                  spacing: 6,
                  runSpacing: 6,
                  children: [for (final fact in facts) _Chip(fact, kTextDim)],
                ),
              ],
            ],
          ),
        ),
      ],
    );
  }
}

class _PendingIdentity extends StatelessWidget {
  final VoidCallback onEnter;
  const _PendingIdentity({required this.onEnter});

  @override
  Widget build(BuildContext context) => _Notice(
    key: const Key('multitracks-identity-pending'),
    icon: Icons.construction,
    color: Colors.orangeAccent,
    text:
        'Detalhes e download ainda não disponíveis para itens da biblioteca: o vínculo entre a música da biblioteca '
        'e o conteúdo usado no download ainda não foi capturado. Nenhuma chamada foi feita.',
    action: TextButton(
      onPressed: onEnter,
      child: const Text('Informar identificador…'),
    ),
  );
}

/// Capa remota opcional; sem rede ou sem imagem, um ícone.
class MultiTracksCover extends StatelessWidget {
  final String? url;
  final double size;
  const MultiTracksCover({super.key, required this.url, this.size = 48});

  @override
  Widget build(BuildContext context) {
    final placeholder = Container(
      width: size,
      height: size,
      color: kPanelBg,
      child: Icon(Icons.music_note, color: kTextDim, size: size / 2),
    );
    final source = url;
    if (source == null || !source.startsWith('https://')) {
      return ClipRRect(
        borderRadius: BorderRadius.circular(6),
        child: placeholder,
      );
    }
    return ClipRRect(
      borderRadius: BorderRadius.circular(6),
      child: Image.network(
        source,
        width: size,
        height: size,
        fit: BoxFit.cover,
        errorBuilder: (_, _, _) => placeholder,
        excludeFromSemantics: true,
      ),
    );
  }
}

class _Notice extends StatelessWidget {
  final IconData icon;
  final Color color;
  final String text;
  final Widget? action;
  const _Notice({
    super.key,
    required this.icon,
    required this.color,
    required this.text,
    this.action,
  });

  @override
  Widget build(BuildContext context) => Container(
    margin: const EdgeInsets.symmetric(vertical: 8),
    padding: const EdgeInsets.all(12),
    decoration: BoxDecoration(
      color: color.withValues(alpha: 0.1),
      borderRadius: BorderRadius.circular(8),
      border: Border.all(color: color.withValues(alpha: 0.45)),
    ),
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(icon, color: color, size: 20),
            const SizedBox(width: 10),
            Expanded(
              child: Text(text, style: const TextStyle(color: kText)),
            ),
          ],
        ),
        if (action != null)
          Align(alignment: Alignment.centerRight, child: action),
      ],
    ),
  );
}

class _SectionTitle extends StatelessWidget {
  final String text;
  const _SectionTitle(this.text);
  @override
  Widget build(BuildContext context) => Padding(
    padding: const EdgeInsets.only(bottom: 8),
    child: Text(
      text.toUpperCase(),
      style: const TextStyle(color: kTextDim, fontSize: 12, letterSpacing: 1),
    ),
  );
}

class _Chip extends StatelessWidget {
  final String label;
  final Color color;
  const _Chip(this.label, this.color);
  @override
  Widget build(BuildContext context) => Container(
    padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 2),
    decoration: BoxDecoration(
      color: color.withValues(alpha: 0.15),
      borderRadius: BorderRadius.circular(4),
      border: Border.all(color: color),
    ),
    child: Text(label, style: TextStyle(color: color, fontSize: 12)),
  );
}

String _formatDate(DateTime utc) {
  final local = utc.toLocal();
  String two(int n) => n.toString().padLeft(2, '0');
  return '${two(local.day)}/${two(local.month)}/${local.year} ${two(local.hour)}:${two(local.minute)}';
}
