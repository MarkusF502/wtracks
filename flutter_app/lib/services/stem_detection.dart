/// Reconhecimento dos stems de um multitrack pelo nome do arquivo (Playback: `MetadataTrack.clickorguide`, `vocal`, `title`).
/// Os nomes variam muito entre produtores ("01 Click.wav", "Drums_Stereo.wav", "GUIA-VOZ.aif"); a detecção é uma sugestão, e o usuário
/// pode renomear, trocar o tipo e reordenar antes de importar (escolha própria: o Playback recebe esses dados prontos do servidor).
class StemGuess {
  /// Nome sugerido para o canal (amigável, em português quando o instrumento é conhecido).
  final String label;

  /// Click ou guia falada: fica fora do fade e do envio ao público (ver `ChannelInfo.isClickOrGuide`).
  final bool isClickOrGuide;

  /// 0 = click, 1 = guia, 2 = qualquer outro (usado para colocar click e guia primeiro, como nos multitracks do Playback).
  final int rank;
  const StemGuess(this.label, this.isClickOrGuide, this.rank);
}

/// Extensões de áudio que o motor lê (JUCE: WAV, AIFF, FLAC).
const importableAudioExtensions = ['wav', 'wave', 'aif', 'aiff', 'flac'];

bool isImportableAudio(String fileName) {
  final dot = fileName.lastIndexOf('.');
  return dot >= 0 && importableAudioExtensions.contains(fileName.substring(dot + 1).toLowerCase());
}

String _strip(String s) {
  const from = 'áàâãäéèêëíìîïóòôõöúùûüç';
  const to = 'aaaaaeeeeiiiiooooouuuuc';
  final buffer = StringBuffer();
  for (final rune in s.toLowerCase().runes) {
    final ch = String.fromCharCode(rune);
    final i = from.indexOf(ch);
    buffer.write(i >= 0 ? to[i] : ch);
  }
  return buffer.toString();
}

/// Nome do arquivo sem pasta, sem extensão de áudio e sem o número de ordem inicial ("01 - ", "3_").
String stemBaseName(String path) {
  var name = path.split('/').last.split(r'\').last;
  final dot = name.lastIndexOf('.');
  if (dot > 0 && isImportableAudio(name)) name = name.substring(0, dot);
  return name.replaceFirst(RegExp(r'^\s*\d{1,3}\s*[-_. )]+\s*'), '').trim();
}

const _known = <(List<String>, String)>[
  (['drum', 'drums', 'bateria', 'kit'], 'Bateria'),
  (['bass', 'baixo', 'bx'], 'Baixo'),
  (['perc', 'percussion', 'percussao'], 'Percussão'),
  (['key', 'keys', 'keyboard', 'teclado', 'teclas', 'piano', 'organ', 'orgao', 'synth', 'sintetizador'], 'Teclas'),
  (['pad', 'pads', 'ambient'], 'Pad'),
  (['acoustic', 'acustico', 'violao'], 'Violão'),
  (['guitar', 'guitarra', 'gtr', 'gtrs', 'eg', 'electric'], 'Guitarra'),
  (['string', 'strings', 'cordas', 'orchestra', 'orquestra', 'brass', 'sopros'], 'Cordas/Sopros'),
  (['bvs', 'bv', 'backing', 'backvocal', 'backvocals', 'coro', 'choir'], 'Backing vocal'),
  (['vocal', 'vocals', 'vox', 'voz', 'lead', 'ref', 'reference', 'referencia'], 'Voz'),
];

List<String> _tokens(String name) =>
    _strip(name).split(RegExp(r'[^a-z0-9]+')).where((t) => t.isNotEmpty).toList();

/// Sugere nome e tipo do canal a partir do nome do arquivo.
StemGuess guessStem(String path) {
  final base = stemBaseName(path);
  final tokens = _tokens(base);
  bool has(List<String> words) => tokens.any(words.contains);
  final lower = _strip(base);

  if (has(const ['click', 'clicks', 'metronome', 'metronomo', 'met']) || lower.contains('click')) return const StemGuess('Click', true, 0);
  if (has(const ['guide', 'guides', 'guia', 'guias', 'cue', 'cues']) || lower.contains('guia')) {
    // "Guia de voz" e "Voice guide" são a guia falada; "guitar guide" seria outro instrumento, mas é raro e o usuário corrige.
    return const StemGuess('Guia', true, 1);
  }
  // "Backing vocal" antes de "Voz": a primeira correspondência na ordem da tabela vence para nomes como "Vocal BV".
  for (final (words, label) in _known) {
    if (has(words)) return StemGuess(label, false, 2);
  }
  return StemGuess(base.isEmpty ? 'Faixa' : base, false, 2);
}

/// Ordem sugerida para os canais: click, guia, depois os demais na ordem em que chegaram. Estável.
List<int> suggestedOrder(List<StemGuess> guesses) {
  final indexes = List<int>.generate(guesses.length, (i) => i);
  indexes.sort((a, b) {
    final byRank = guesses[a].rank.compareTo(guesses[b].rank);
    return byRank != 0 ? byRank : a.compareTo(b);
  });
  return indexes;
}

/// Nomes repetidos ganham um número ("Guitarra", "Guitarra 2"), para o mixer não mostrar dois canais iguais.
List<String> uniqueLabels(List<String> labels) {
  final seen = <String, int>{};
  return [
    for (final label in labels)
      () {
        final count = (seen[label] ?? 0) + 1;
        seen[label] = count;
        return count == 1 ? label : '$label $count';
      }(),
  ];
}
