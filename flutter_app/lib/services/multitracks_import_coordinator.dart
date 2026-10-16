import 'dart:async';
import 'dart:io';
import 'dart:isolate';

import 'package:flutter/services.dart';

import '../models/multitracks_import_job.dart';
import '../models/multitracks_origin.dart';
import '../models/multitracks_song_details.dart';
import '../models/track.dart';
import 'multitracks_content_provider.dart';
import 'multitracks_contract.dart';
import 'multitracks_package_downloader.dart';
import 'multitracks_package_importer.dart';

/// Sinal de cancelamento que atravessa isolates: o importador consulta [isCancelled] entre blocos e faixas.
class MultiTracksCancellation {
  final _completer = Completer<void>();
  bool get isCancelled => _completer.isCompleted;
  Future<void> get whenCancelled => _completer.future;
  void cancel() {
    if (!_completer.isCompleted) _completer.complete();
  }
}

/// Eventos de progresso do importador.
sealed class MultiTracksImportEvent {
  const MultiTracksImportEvent();
}

class MultiTracksStageEvent extends MultiTracksImportEvent {
  final MultiTracksPackageStage stage;
  const MultiTracksStageEvent(this.stage);
}

class MultiTracksStemEvent extends MultiTracksImportEvent {
  final int index, total;
  final String label;
  const MultiTracksStemEvent(this.index, this.total, this.label);
}

class MultiTracksImportTask {
  final String packagePath, destinationPath;
  final MultiTracksContentItem item;
  final MultiTracksContentSelection selection;
  const MultiTracksImportTask({
    required this.packagePath,
    required this.destinationPath,
    required this.item,
    required this.selection,
  });
}

/// Onde o importador roda. Em produção, num isolate próprio: LZ4, ZIP e CRC não podem bloquear quadros da interface.
abstract class MultiTracksImportRunner {
  Future<MultiTracksImportedContent> run(
    MultiTracksImportTask task, {
    required MultiTracksCancellation cancellation,
    required void Function(MultiTracksImportEvent event) onEvent,
  });
}

/// No mesmo isolate (testes e transcoders falsos).
class InlineMultiTracksImportRunner implements MultiTracksImportRunner {
  const InlineMultiTracksImportRunner(this.importer);
  final MultiTracksPackageImporter importer;

  @override
  Future<MultiTracksImportedContent> run(
    MultiTracksImportTask task, {
    required MultiTracksCancellation cancellation,
    required void Function(MultiTracksImportEvent event) onEvent,
  }) =>
      importer.import(
        package: File(task.packagePath),
        destinationDirectory: Directory(task.destinationPath),
        item: task.item,
        selection: task.selection,
        isCancelled: () => cancellation.isCancelled,
        onStage: (stage) => onEvent(MultiTracksStageEvent(stage)),
        onStemStarted: (index, total, label) => onEvent(MultiTracksStemEvent(index, total, label)),
      );
}

/// Roda o importador num isolate de segundo plano com o transcoder Android (o canal de plataforma funciona ali pelo
/// [BackgroundIsolateBinaryMessenger]). O cancelamento chega por mensagem e é verificado entre blocos/faixas.
class IsolateMultiTracksImportRunner implements MultiTracksImportRunner {
  const IsolateMultiTracksImportRunner();

  @override
  Future<MultiTracksImportedContent> run(
    MultiTracksImportTask task, {
    required MultiTracksCancellation cancellation,
    required void Function(MultiTracksImportEvent event) onEvent,
  }) async {
    final token = RootIsolateToken.instance;
    if (token == null) throw const MultiTracksPackageImportFailure('Importação em segundo plano indisponível');
    final messages = ReceivePort();
    final errors = ReceivePort();
    final result = Completer<MultiTracksImportedContent>();
    SendPort? control;
    final isolate = await Isolate.spawn(_importInBackground, (task, messages.sendPort, token),
        onError: errors.sendPort, errorsAreFatal: true);
    unawaited(cancellation.whenCancelled.then((_) => control?.send(true)));
    errors.listen((error) {
      if (!result.isCompleted) result.completeError(const MultiTracksPackageImportFailure('Falha interna na importação'));
    });
    messages.listen((message) {
      switch (message) {
        case SendPort port:
          control = port;
          if (cancellation.isCancelled) port.send(true);
        case MultiTracksImportEvent event:
          onEvent(event);
        case MultiTracksImportedContent content:
          if (!result.isCompleted) result.complete(content);
        case (String failure,):
          if (!result.isCompleted) result.completeError(MultiTracksPackageImportFailure(failure));
      }
    });
    try {
      return await result.future;
    } finally {
      messages.close();
      errors.close();
      isolate.kill(priority: Isolate.immediate);
    }
  }
}

Future<void> _importInBackground((MultiTracksImportTask, SendPort, RootIsolateToken) args) async {
  final (task, out, token) = args;
  BackgroundIsolateBinaryMessenger.ensureInitialized(token);
  final control = ReceivePort();
  var cancelled = false;
  control.listen((_) => cancelled = true);
  out.send(control.sendPort);
  try {
    final content = await MultiTracksPackageImporter(transcoder: const AndroidMultiTracksAudioTranscoder()).import(
      package: File(task.packagePath),
      destinationDirectory: Directory(task.destinationPath),
      item: task.item,
      selection: task.selection,
      isCancelled: () => cancelled,
      onStage: (stage) => out.send(MultiTracksStageEvent(stage)),
      onStemStarted: (index, total, label) => out.send(MultiTracksStemEvent(index, total, label)),
    );
    out.send(content);
  } on MultiTracksPackageImportFailure catch (error) {
    out.send((error.message,));
  } on Object catch (error) {
    out.send(('${error.runtimeType}',));
  } finally {
    control.close();
  }
}

class MultiTracksRentalPrompt {
  final String title;
  final String? keyTitle;
  final int? rentalsRemaining;
  final DateTime? expiresAt;
  const MultiTracksRentalPrompt({required this.title, this.keyTitle, this.rentalsRemaining, this.expiresAt});
}

typedef MultiTracksRentalConfirmation = Future<bool> Function(MultiTracksRentalPrompt prompt);
typedef MultiTracksPublish = Future<Track> Function(MultiTracksImportedContent content, MultiTracksOrigin origin);

class MultiTracksImportRequest {
  final MultiTracksSongDetails details;
  final int? libraryId;
  const MultiTracksImportRequest(this.details, {this.libraryId});
}

class _Cancelled implements Exception {
  const _Cancelled();
}

class _Failure implements Exception {
  final String message;
  const _Failure(this.message);
}

/// Orquestra link → (Rental confirmado) → download → validação → extração → conversão → salvamento, publicando cada
/// etapa em [onUpdate]. Regras: um trabalho ativo por `contentId:keyId`; `redeemRental` só depois de confirmação
/// explícita e nunca repetido (nem após timeout, nem num novo trabalho da mesma sessão); nada entra na biblioteca antes
/// de todas as validações; staging sempre apagado no fim.
class MultiTracksImportCoordinator {
  MultiTracksImportCoordinator({
    required this.content,
    required this.downloader,
    required this.runner,
    required this.stagingRoot,
    required this.publish,
    required this.onUpdate,
    this.freeBytes,
    DateTime Function()? clock,
  }) : _clock = clock ?? DateTime.now;

  final MultiTracksContentProvider content;
  final MultiTracksPackageDownloader downloader;
  final MultiTracksImportRunner runner;
  final Future<Directory> Function() stagingRoot;
  final MultiTracksPublish publish;
  final void Function(MultiTracksImportJob job) onUpdate;

  /// Espaço livre no volume de [path]; `null` quando a plataforma não informa.
  final Future<int?> Function(String path)? freeBytes;
  final DateTime Function() _clock;

  final _active = <String, Future<MultiTracksImportJob>>{};
  final _cancellations = <String, MultiTracksCancellation>{};

  /// Pares `contentId:keyId` cujo aluguel já foi pedido nesta execução: nunca pedir de novo automaticamente.
  final _redeemed = <String>{};

  bool isActive(String key) => _active.containsKey(key);

  void cancel(String key) => _cancellations[key]?.cancel();

  /// Esquece aluguéis pedidos (logout/troca de conta).
  void resetSession() => _redeemed.clear();

  /// Remove staging deixado por um processo encerrado no meio de uma importação.
  Future<void> cleanStaleStaging() async {
    final root = await stagingRoot();
    if (!await root.exists()) return;
    await for (final entry in root.list()) {
      if (_active.keys.any((key) => entry.path.endsWith('/${_stagingName(key)}'))) continue;
      try {
        await entry.delete(recursive: true);
      } on FileSystemException {
        // tenta de novo na próxima abertura
      }
    }
  }

  Future<MultiTracksImportJob> start(MultiTracksImportRequest request, {required MultiTracksRentalConfirmation confirmRental}) {
    final selection = request.details.selection;
    final key = MultiTracksImportJob.keyFor(selection.contentId, selection.keyId);
    final running = _active[key];
    if (running != null) return running;
    final cancellation = MultiTracksCancellation();
    _cancellations[key] = cancellation;
    final job = _run(key, request, cancellation, confirmRental).whenComplete(() {
      _active.remove(key);
      _cancellations.remove(key);
    });
    _active[key] = job;
    return job;
  }

  String _stagingName(String key) => key.replaceAll(':', '-');

  Future<MultiTracksImportJob> _run(
    String key,
    MultiTracksImportRequest request,
    MultiTracksCancellation cancellation,
    MultiTracksRentalConfirmation confirmRental,
  ) async {
    final details = request.details;
    final selection = details.selection;
    var job = MultiTracksImportJob(key: key, title: details.title, keyTitle: details.selectedKeyTitle);
    void emit(MultiTracksImportJob next) {
      job = next;
      onUpdate(next);
    }

    void checkCancelled() {
      if (cancellation.isCancelled) throw const _Cancelled();
    }

    emit(job);
    Directory? staging;
    try {
      emit(job.copyWith(phase: MultiTracksImportPhase.requestingDownloadLink));
      var link = await _requestLink(selection);
      checkCancelled();
      var item = link.item;
      var entitlement = details.entitlement;
      if (link.url == null) {
        if (_redeemed.contains(key)) {
          throw const _Failure('O aluguel desta música já foi pedido, mas o servidor não liberou o download. '
              'Para não consumir outro crédito, o WTracks não repete o pedido. Tente mais tarde.');
        }
        if (!details.rentalPossible) {
          throw const _Failure('A conta não recebeu autorização de download para esta música.');
        }
        emit(job.copyWith(phase: MultiTracksImportPhase.awaitingRentalConfirmation));
        final confirmed = await confirmRental(MultiTracksRentalPrompt(
          title: details.title,
          keyTitle: details.selectedKeyTitle,
          rentalsRemaining: details.rentalsRemaining,
          expiresAt: details.entitlement.expiresAt,
        ));
        if (!confirmed) throw const _Cancelled();
        checkCancelled();

        // Antes da chamada: uma resposta perdida também conta como pedido (crédito possivelmente consumido).
        _redeemed.add(key);
        emit(job.copyWith(phase: MultiTracksImportPhase.redeemingRental, rentalRedeemed: true));
        final (redeemed, reconciled) = await _redeem(selection);
        link = redeemed;
        item = link.item ?? item;
        if (link.url == null && !reconciled) {
          // Resgate aceito sem link: uma única consulta de link, sem resgatar de novo.
          link = await _requestLink(selection);
          item = link.item ?? item;
        }
        if (link.url == null) {
          throw const _Failure('O aluguel foi pedido, mas o download não foi liberado. O pedido não será repetido '
              'automaticamente; confira o estado da música antes de tentar outra vez.');
        }
        final rented = item == null ? null : MultiTracksSongDetails.entitlementOf(item, null);
        entitlement = rented != null && rented.kind != MultiTracksEntitlementKind.unknown
            ? rented
            : const MultiTracksEntitlement(MultiTracksEntitlementKind.rental);
      } else if (item != null && entitlement.kind == MultiTracksEntitlementKind.unknown) {
        entitlement = MultiTracksSongDetails.entitlementOf(item, null);
      }
      checkCancelled();

      // Os descritores de faixa vêm da resposta mais recente; se ela não os trouxe, os da consulta de detalhes.
      final manifest = item != null && item.stems.isNotEmpty ? item : details.item;

      // Disco só a partir daqui: consulta e Rental não deixam nada no aparelho.
      emit(job.copyWith(phase: MultiTracksImportPhase.downloading));
      staging = Directory('${(await stagingRoot()).path}/${_stagingName(key)}');
      if (await staging.exists()) await staging.delete(recursive: true);
      await staging.create(recursive: true);
      checkCancelled();
      final MultiTracksDownloadedPackage package;
      try {
        package = await downloader.download(
          url: Uri.parse(link.url!),
          destinationDirectory: staging,
          packageId: selection.contentId,
          isCancelled: () => cancellation.isCancelled,
          onProgress: (received, total) => emit(job.copyWith(receivedBytes: received, totalBytes: total)),
        );
      } on MultiTracksDownloadCancelled {
        throw const _Cancelled();
      } on MultiTracksDownloadFailure catch (error) {
        throw _Failure(_downloadMessage(error));
      } on FormatException {
        throw const _Failure('Link de download inválido.');
      }
      link = const _Link(null, null); // a URL assinada não fica guardada além do necessário
      checkCancelled();

      final needed = estimateImportBytes(package.length);
      final free = await freeBytes?.call(staging.path);
      if (free != null && free < needed) {
        throw _Failure('Espaço insuficiente: a conversão para WAV precisa de cerca de ${formatBytes(needed)} '
            '(estimativa) e há ${formatBytes(free)} livres.');
      }

      emit(job.copyWith(phase: MultiTracksImportPhase.validating));
      final MultiTracksImportedContent imported;
      try {
        imported = await runner.run(
          MultiTracksImportTask(
            packagePath: package.file.path,
            destinationPath: '${staging.path}/audio',
            item: manifest,
            selection: selection,
          ),
          cancellation: cancellation,
          onEvent: (event) => switch (event) {
            MultiTracksStageEvent(:final stage) => emit(job.copyWith(phase: switch (stage) {
                MultiTracksPackageStage.validating => MultiTracksImportPhase.validating,
                MultiTracksPackageStage.extracting => MultiTracksImportPhase.extracting,
                MultiTracksPackageStage.transcoding => MultiTracksImportPhase.transcoding,
              })),
            MultiTracksStemEvent(:final index, :final total, :final label) =>
              emit(job.copyWith(phase: MultiTracksImportPhase.transcoding, stemIndex: index, stemCount: total, stemLabel: label)),
          },
        );
      } on MultiTracksPackageImportFailure catch (error) {
        if (cancellation.isCancelled) throw const _Cancelled();
        throw _Failure('Pacote inválido ou não suportado: ${_safeDetail(error.message)}');
      }
      checkCancelled();
      // Pacotes já não são necessários: só os WAV seguem para a biblioteca.
      await _deleteQuietly(package.file);

      emit(job.copyWith(phase: MultiTracksImportPhase.saving, stemIndex: job.stemCount, stemLabel: null));
      final origin = MultiTracksOrigin(
        contentId: selection.contentId,
        libraryId: request.libraryId ?? details.item.libraryId,
        keyId: selection.keyId,
        contentType: selection.contentType,
        stemsVersion: details.stemsVersion,
        packageVersion: details.packageVersion,
        entitlementKind: entitlement.kind,
        entitlementExpiresAt: entitlement.expiresAt,
        lastValidatedAt: _clock().toUtc(),
      );
      final Track saved;
      try {
        saved = await publish(imported, origin);
      } on Object catch (error) {
        throw _Failure('Não foi possível salvar na biblioteca: ${_safeDetail(error.toString())}');
      }
      emit(job.copyWith(phase: MultiTracksImportPhase.completed, track: saved, message: null));
      return job;
    } on _Cancelled {
      emit(job.copyWith(
        phase: MultiTracksImportPhase.cancelled,
        message: job.rentalRedeemed ? 'Importação cancelada. O crédito de aluguel já confirmado não é devolvido automaticamente.' : null,
      ));
      return job;
    } on Object catch (error) {
      final failedAt = job.phase;
      emit(job.copyWith(phase: MultiTracksImportPhase.failed, failedPhase: failedAt, message: _messageFor(error, failedAt)));
      return job;
    } finally {
      if (staging != null) await _deleteQuietly(staging);
    }
  }

  Future<_Link> _requestLink(MultiTracksContentSelection selection) async =>
      _Link.from(selection, await content.requestDownloadLink(selection));

  /// Uma única tentativa. Se a resposta se perder (timeout, rede, formato), reconcilia com uma consulta de link sem
  /// resgatar; o resgate em si nunca é repetido.
  /// Devolve também se a resposta já veio da consulta de reconciliação (para não consultar outra vez).
  Future<(_Link, bool)> _redeem(MultiTracksContentSelection selection) async {
    try {
      return (_Link.from(selection, await content.redeemRental(selection)), false);
    } on MultiTracksStaleSession {
      rethrow;
    } on _ResponseFailure {
      rethrow; // recusa explícita do servidor: não é resposta ambígua
    } on Object {
      try {
        return (await _requestLink(selection), true);
      } on Object {
        throw const _Failure('Não foi possível confirmar se o aluguel foi registrado. O pedido não foi repetido; '
            'consulte a música novamente antes de tentar outra vez.');
      }
    }
  }

  static String _messageFor(Object error, MultiTracksImportPhase phase) => switch (error) {
        _Failure(:final message) => message,
        _ResponseFailure(:final message) => message,
        MultiTracksStaleSession() => 'A sessão MultiTracks mudou durante a importação. Entre novamente.',
        MultiTracksHttpFailure(:final statusCode) when statusCode == 401 || statusCode == 403 =>
          'A sessão MultiTracks expirou. Entre novamente.',
        MultiTracksHttpFailure(:final statusCode) => 'O servidor MultiTracks respondeu HTTP $statusCode.',
        SocketException() || TimeoutException() || HttpException() => 'Falha de rede durante "${phase.label}".',
        FileSystemException() => 'Falha de armazenamento durante "${phase.label}".',
        _ => 'Falha inesperada durante "${phase.label}".',
      };

  static String _downloadMessage(MultiTracksDownloadFailure error) => switch (error.message) {
        'Content-MD5 mismatch' => 'O pacote chegou corrompido (MD5 diferente). Tente novamente.',
        'Incomplete package' => 'O download terminou incompleto. Tente novamente.',
        'Untrusted download URL' || 'Invalid download redirect' || 'Too many redirects' =>
          'O link de download não é de um servidor confiável.',
        final message when message.startsWith('Unexpected download status') =>
          'O link de download foi recusado (pode ter expirado). Tente novamente para pedir um novo link.',
        _ => 'Falha no download: ${_safeDetail(error.message)}',
      };

  Future<void> _deleteQuietly(FileSystemEntity entity) async {
    try {
      if (await entity.exists()) await entity.delete(recursive: true);
    } on FileSystemException {
      // sobra no cache; cleanStaleStaging remove na próxima abertura
    }
  }
}

class _ResponseFailure implements Exception {
  final String message;
  const _ResponseFailure(this.message);
}

class _Link {
  final String? url;
  final MultiTracksContentItem? item;
  const _Link(this.url, this.item);

  /// Sucesso exige `result: 1` e `errorCode: 0`; a URL só vale se não estiver vazia.
  factory _Link.from(MultiTracksContentSelection selection, MultiTracksContentResponse response) {
    if (!response.isSuccess) {
      throw _ResponseFailure('O servidor recusou o pedido (resultado ${response.result}, erro ${response.errorCode}).');
    }
    final item = response.items.where((i) => i.contentId == null || i.contentId == selection.contentId).firstOrNull;
    final url = item?.downloadUrl;
    return _Link(url != null && url.isNotEmpty ? url : null, item);
  }
}

/// Remove trechos com aparência de caminho ou URL de mensagens técnicas.
String _safeDetail(String message) {
  final cleaned = message
      .split(RegExp(r'\s+'))
      .where((word) => !word.contains('/') && !word.contains(r'\') && !word.contains('://') && !word.contains('?'))
      .join(' ');
  return cleaned.length <= 160 ? cleaned : '${cleaned.substring(0, 157)}…';
}

String formatBytes(int bytes) {
  const units = ['B', 'KB', 'MB', 'GB', 'TB'];
  var value = bytes.toDouble();
  var unit = 0;
  while (value >= 1024 && unit < units.length - 1) {
    value /= 1024;
    unit++;
  }
  return '${value.toStringAsFixed(unit == 0 ? 0 : 1)} ${units[unit]}';
}
