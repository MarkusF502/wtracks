# Auditoria Android — download/importação MultiTracks (2026-10-16)

**Resultado revisado: VALIDADO para a oferta semanal, com limites.** O backup criado no aparelho comprova que um build
anterior do WTracks publicou a música semanal como uma Track `multitracks-…`, com 11 WAVs produzidos a partir dos stems.
O motor do aparelho carregou essa Track e avançou o transporte, e o responsável confirmou a reprodução fisicamente
audível dos stems, metrônomo e guia. Continua sem comprovação independente a requisição HTTP histórica; compras
permanentes, Rental paga e ciclo de expiração não foram testados.

## 1. Correção da conclusão inicial

O APK atualmente instalado (`versionCode 2007`, atualizado em 2026-10-15 às 18:42) não contém a integração MultiTracks.
Esse achado permanece correto, mas não impede que a importação tenha ocorrido antes: um APK local com a integração foi
gerado às 15:36, usa o mesmo pacote e o mesmo certificado e pôde ser substituído pelo APK 2007 sem apagar os dados.

O backup posterior resolveu a ambiguidade. Ele contém uma Track cujo ID segue exatamente o formato produzido pelo
`MultiTracksPackageImporter`, além da pasta de áudio correspondente. Portanto, a ausência da integração no APK atual
explica por que novas importações deixaram de funcionar, mas não invalida a importação anterior preservada nos dados.

## 2. Dispositivo, aplicativo e backup

| Item | Evidência |
|---|---|
| Aparelho | Xiaomi 23053RN02A (`fire_global`), Android 15, arm64-v8a |
| Aplicativo atual | `com.example.flutter_app`, 1.0.0, `versionCode 2007` |
| Atualização atual | 2026-10-15 18:42:37, APK de CI sem a integração |
| Build anterior compatível | APK local de 2026-10-15 15:36, com integração e mesmo certificado |
| Backup | `wtracks-backup-2026-10-16-1346.zip`, criado em 2026-10-16 16:47:08Z |
| Conteúdo do backup | 3 músicas, 1 setlist e 22 arquivos de áudio |
| Integridade do ZIP | `unzip -t`: nenhum erro em todas as entradas |

O backup foi copiado para uma pasta temporária com permissão restrita. Só o manifesto, o JSON da Track e os 11 WAVs
relevantes foram inspecionados. Nenhum áudio foi incluído no repositório ou no relatório.

## 3. Evidência persistida da importação

O backup contém:

- `tracks/multitracks-…-….json`;
- a pasta `audio/multitracks-…-…/`;
- 11 WAVs no formato `v<versão>-<ordem>-<stemID>.wav`;
- 11 canais no JSON, apontando exatamente para esses 11 arquivos;
- tonalidade selecionada persistida;
- dois canais marcados com `isClickOrGuide: true` e `excludeFromFade: true`;
- rótulos coerentes para metrônomo, guia, instrumentos, vozes e música original.

O campo `origin` não está mais no JSON do backup. O APK 2007 não conhece esse campo e pode descartá-lo quando regrava a
Track. Essa perda impede usar `origin.entitlementKind` como recibo, mas não elimina as evidências específicas do importador:
o ID `multitracks-…-…`, o diretório com o mesmo ID, os nomes terminados nos `stemID` observados e a correspondência exata
entre JSON e WAVs são gerados em conjunto pelo caminho MultiTracks do worktree.

## 4. Validação dos 11 WAVs

| Verificação | Resultado |
|---|---|
| Entradas no manifesto | 11 |
| Canais no JSON | 11 |
| JSON ↔ arquivos | correspondência exata 11/11 |
| Tamanho ↔ manifesto | 11/11 |
| SHA-256 ↔ manifesto | 11/11 |
| Formato | RIFF/WAVE, Microsoft PCM |
| Resolução | 16 bits, estéreo, 44,1 kHz |
| Tamanho por stem | 47.138.520 bytes, igual nos 11 |
| Duração derivada | aproximadamente 267,225 s em todos os stems |
| Click/guia | 2 canais identificados |

O teste CRC do ZIP de backup passou integralmente. Esses resultados demonstram que a conversão no Android produziu
arquivos completos, alinhados em duração e utilizáveis pelo motor.

## 5. Execução no aparelho

A Track foi selecionada na biblioteca do APK atualmente instalado e carregada sem erro. A tela mostrou duração total de
4:27, compatível com os 267,225 segundos dos WAVs. Ao iniciar o transporte, o contador avançou de 0:00 para 0:08 e o
controle mudou de **Tocar** para **Pausar**. Não houve aviso do processo do WTracks no `logcat` durante esse intervalo.

A tela de faixas apresentou os canais persistidos, incluindo metrônomo e guia. Os controles de solo foram acionados e
restaurados, mas o estado não é exposto pela árvore de acessibilidade. Após a coleta automatizada, o responsável confirmou
que ouviu corretamente a música, os stems, o metrônomo e a guia no aparelho.

O responsável também relatou que, antes da otimização da tela de performance, a reprodução simultânea das 11 faixas tinha
travamentos e lentidão. Depois da otimização, a reprodução ficou excelente. Isso é evidência humana de runtime, não uma
medição instrumental de underruns, carga ou latência.

## 6. Cadeia causal no código auditado

| Etapa | Implementação |
|---|---|
| Download privado e validação | `multitracks_package_downloader.dart` |
| LZ4, ZIP, CRC e correspondência por stemID | `multitracks_package_importer.dart` |
| M4A → WAV no Android | `MultiTracksAudioDecoder.kt` |
| ID `multitracks-<contentId>-<keyId>` e nomes com stemID | `multitracks_package_importer.dart` |
| Publicação atômica e persistência | `multitracks_import_coordinator.dart` e `engine_provider.dart` |

No fluxo normal do aplicativo, essa Track só é publicada depois que download, validação, extração e conversão terminam
sem exceção. O `.mtrack`, ZIP e M4A são removidos depois da importação; por isso não estão no backup.

## 7. Conclusão por etapa

| Etapa | Estado |
|---|---|
| Download autorizado da oferta semanal | **Validado por evidência persistida e cadeia causal**, sem recibo HTTP independente |
| Validação/importação do `.mtrack` | **Validada por evidência persistida e cadeia causal** |
| Extração LZ4/ZIP e mapeamento de stems | **Validada** para esta amostra de 11 stems |
| Conversão AAC/M4A → WAV no Android | **Validada**: 11 WAVs PCM íntegros e alinhados |
| Persistência na biblioteca | **Validada**: JSON e arquivos conferem 11/11 |
| Carregamento no motor | **Validado**: duração reconhecida e transporte avançou |
| Reprodução fisicamente audível | **Validada por confirmação humana** para stems, metrônomo e guia |
| Prova histórica independente da transferência HTTP | **Inexistente**: sem captura ou recibo persistente |
| Compra permanente / Rental paga | **Não testadas** |
| Expiração, offline, revogação e transferência | **Não testados** |

Formulação correta para o aceite:

> Download e importação reais da oferta semanal comprovados pelo estado persistido, execução no Android e cadeia causal
> do aplicativo, com reprodução audível confirmada no aparelho; a transferência HTTP passada não possui recibo
> persistente independente.

## 8. Achados adicionais

1. O APK de CI 2007 substituiu o build local com MultiTracks e removeu a capacidade de iniciar novas importações, embora
   os dados já publicados tenham permanecido. A integração precisa entrar no código versionado e numa versão superior.
2. O backup atual inclui os WAVs licenciados da Track MultiTracks. Isso contradiz o requisito do plano de guardar apenas
   referência e metadados para conteúdo protegido e permanece uma pendência antes da liberação.
3. O download só compara MD5 quando o servidor envia `Content-MD5`; sem esse cabeçalho, a integridade estrutural depende
   dos checksums LZ4/ZIP. Nesta amostra, o resultado final persistido passou pelos hashes do backup.
