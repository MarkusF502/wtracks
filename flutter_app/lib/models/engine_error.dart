enum EngineErrorCode {
  none,
  fileUnreadable,
  formatMismatch,
  deviceInitFailed,
  unknown,
}

EngineErrorCode engineErrorCodeFromInt(int value) =>
    value >= 0 && value < EngineErrorCode.values.length
    ? EngineErrorCode.values[value]
    : EngineErrorCode.unknown;

String engineErrorMessage(EngineErrorCode code) => switch (code) {
  EngineErrorCode.fileUnreadable =>
    'Não foi possível ler o áudio. Importe novamente um arquivo válido.',
  EngineErrorCode.formatMismatch =>
    'Os canais precisam ter a mesma taxa de amostragem e durações compatíveis.',
  EngineErrorCode.deviceInitFailed =>
    'Não foi possível iniciar o áudio. Verifique a saída de áudio e reabra o aplicativo.',
  EngineErrorCode.none || EngineErrorCode.unknown =>
    'Não foi possível carregar a música. Tente novamente.',
};
