#!/usr/bin/env bash
# Harness de testes do WTracks -- roda tudo no desktop Linux, sem celular:
#   1. compila o engine nativo (JUCE) para Linux e roda os testes C++
#   2. análise estática do Flutter
#   3. flutter test (unit + widget), com a libwtracks_engine.so real no
#      LD_LIBRARY_PATH para os testes que exercitam o FFI
# Gera um resumo em harness_reports/<data>/summary.md.
#
# Uso: tool/harness/run_harness.sh [--skip-native]

set -uo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
NATIVE="$ROOT/native"
APP="$ROOT/flutter_app"
BUILD="$NATIVE/build-linux"
OUT="$ROOT/harness_reports/$(date +%Y%m%d-%H%M%S)"
mkdir -p "$OUT"

export PATH="${FLUTTER_HOME:-$HOME/development/flutter}/bin:$PATH"

SKIP_NATIVE=0
[[ "${1:-}" == "--skip-native" ]] && SKIP_NATIVE=1

section() { printf '\n\033[1;36m== %s ==\033[0m\n' "$1"; }

# ---------------------------------------------------------------- nativo
native_status="pulado"
if [[ $SKIP_NATIVE -eq 0 ]]; then
  section "Build nativo (Linux)"
  if cmake -S "$NATIVE" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Debug >"$OUT/native_build.log" 2>&1 &&
     cmake --build "$BUILD" -j "$(nproc)" >>"$OUT/native_build.log" 2>&1; then
    section "Testes C++ (juce::UnitTest)"
    "$BUILD/wtracks_engine_tests" >"$OUT/native_tests.log" 2>&1
    native_rc=$?
    grep -E "^Starting tests|!!!" "$OUT/native_tests.log"
    native_status=$([[ $native_rc -eq 0 ]] && echo "ok" || echo "FALHOU")
  else
    native_status="BUILD FALHOU (ver native_build.log)"
    tail -20 "$OUT/native_build.log"
  fi
fi

# ---------------------------------------------------------------- analyze
section "flutter analyze"
cd "$APP"
flutter pub get >/dev/null
flutter analyze >"$OUT/analyze.log" 2>&1
analyze_rc=$?
tail -3 "$OUT/analyze.log"

# ---------------------------------------------------------------- flutter test
section "flutter test"
export LD_LIBRARY_PATH="$BUILD${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
flutter test --reporter json >"$OUT/flutter_tests.jsonl" 2>"$OUT/flutter_tests.stderr"
test_rc=$?

python3 - "$OUT" "$native_status" "$analyze_rc" <<'PY'
import json, re, sys, pathlib
out, native_status, analyze_rc = pathlib.Path(sys.argv[1]), sys.argv[2], sys.argv[3]

tests, results, errors = {}, {}, {}
for line in (out / "flutter_tests.jsonl").read_text().splitlines():
    try:
        ev = json.loads(line)
    except json.JSONDecodeError:
        continue
    t = ev.get("type")
    if t == "testStart":
        tests[ev["test"]["id"]] = ev["test"]["name"]
    elif t == "testDone" and not ev.get("hidden"):
        results[ev["testID"]] = "skip" if ev.get("skipped") else ev["result"]
    elif t == "error":
        errors.setdefault(ev["testID"], []).append(ev["error"])

passed = [tests[i] for i, r in results.items() if r == "success"]
failed = [i for i, r in results.items() if r in ("failure", "error")]
skipped = [tests[i] for i, r in results.items() if r == "skip"]

native_log = (out / "native_tests.log")
native_fail = []
if native_log.exists():
    cur = None
    for l in native_log.read_text(errors="replace").splitlines():
        if l.startswith("Starting tests in:"):
            cur = l.split(":", 1)[1].strip().rstrip(".")
        elif l.startswith("!!!"):
            native_fail.append(f"{cur}: {l[4:].strip()}")

lines = ["# Relatório do harness", "",
         f"- Testes C++: **{native_status}** ({len(native_fail)} asserções falhando)",
         f"- flutter analyze: **{'ok' if analyze_rc == '0' else 'com issues'}**",
         f"- flutter test: **{len(passed)} ok, {len(failed)} falhando, {len(skipped)} pulados**", ""]
if native_fail:
    lines += ["## Falhas C++", ""] + [f"- {f}" for f in native_fail] + [""]
if failed:
    lines += ["## Falhas Flutter", ""]
    for i in failed:
        msg = " / ".join(e.splitlines()[0] for e in errors.get(i, []))[:300]
        lines.append(f"- **{tests[i]}** — {msg}")
    lines.append("")
if skipped:
    lines += ["## Pulados", ""] + [f"- {s}" for s in skipped] + [""]
(out / "summary.md").write_text("\n".join(lines))
print("\n".join(lines))
PY

section "Relatórios em $OUT"
[[ "$native_status" == "ok" || "$native_status" == "pulado" ]] && [[ $test_rc -eq 0 ]]
