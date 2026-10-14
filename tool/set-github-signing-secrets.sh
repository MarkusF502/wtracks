#!/usr/bin/env bash
# Cadastra no GitHub os secrets de assinatura do APK (ver docs/ASSINATURA-ANDROID.md).
# Uso: tool/set-github-signing-secrets.sh [keystore] [alias]
#   keystore  padrão: ~/.android/debug.keystore (opção A: a chave do app já instalado)
#   alias     padrão: androiddebugkey
# As senhas são pedidas no terminal (o padrão da chave de debug é "android"). Nada é gravado em disco nem no histórico.
# Precisa do GitHub CLI autenticado: https://cli.github.com  (gh auth login)
set -euo pipefail

REPO="${WTRACKS_REPO:-MarkusF502/wtracks}"
KEYSTORE="${1:-$HOME/.android/debug.keystore}"
ALIAS="${2:-androiddebugkey}"

command -v gh >/dev/null || { echo "Instale o GitHub CLI (https://cli.github.com) e rode 'gh auth login'." >&2; exit 1; }
gh auth status >/dev/null 2>&1 || { echo "gh não está autenticado: rode 'gh auth login'." >&2; exit 1; }
[ -f "$KEYSTORE" ] || { echo "Keystore não encontrado: $KEYSTORE" >&2; exit 1; }
KEYTOOL="$(command -v keytool || echo /opt/android-studio/jbr/bin/keytool)"

read -rsp "Senha do keystore: " STOREPASS; echo
read -rsp "Senha da chave (Enter = a mesma): " KEYPASS; echo
KEYPASS="${KEYPASS:-$STOREPASS}"

# Confere as senhas e pega o certificado ANTES de enviar qualquer coisa.
SHA=$("$KEYTOOL" -list -v -keystore "$KEYSTORE" -storepass "$STOREPASS" -alias "$ALIAS" 2>/dev/null \
  | awk -F': ' '/SHA256:/ {gsub(":", "", $2); print toupper($2); exit}')
[ -n "$SHA" ] || { echo "Não consegui ler o certificado: senha ou alias errados." >&2; exit 1; }
echo "Certificado: $SHA"
read -rp "Enviar a chave e as senhas para os secrets de $REPO? [s/N] " OK
[ "$OK" = "s" ] || { echo "Cancelado."; exit 1; }

base64 -w0 "$KEYSTORE" | gh secret set WTRACKS_KEYSTORE_BASE64 --repo "$REPO"
printf '%s' "$STOREPASS" | gh secret set WTRACKS_KEYSTORE_PASSWORD --repo "$REPO"
printf '%s' "$ALIAS" | gh secret set WTRACKS_KEY_ALIAS --repo "$REPO"
printf '%s' "$KEYPASS" | gh secret set WTRACKS_KEY_PASSWORD --repo "$REPO"
gh variable set WTRACKS_RELEASE_CERT_SHA256 --body "$SHA" --repo "$REPO"
echo "Pronto. O próximo push assina com essa chave e o CI confere o certificado ($SHA)."
