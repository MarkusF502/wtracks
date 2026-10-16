import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../providers/multitracks_provider.dart';
import '../theme/app_colors.dart';

/// Login MultiTracks, mostrado pela [MultiTracksLibraryScreen] enquanto não há sessão. A senha fica só no controller
/// durante a chamada e é apagada depois do sucesso (e com o descarte da tela).
class MultiTracksLoginPanel extends ConsumerStatefulWidget {
  const MultiTracksLoginPanel({super.key});

  @override
  ConsumerState<MultiTracksLoginPanel> createState() => _MultiTracksLoginPanelState();
}

class _MultiTracksLoginPanelState extends ConsumerState<MultiTracksLoginPanel> {
  final _username = TextEditingController();
  final _password = TextEditingController();
  final _passwordFocus = FocusNode();
  bool _obscure = true;

  @override
  void dispose() {
    _password.clear();
    _username.dispose();
    _password.dispose();
    _passwordFocus.dispose();
    super.dispose();
  }

  Future<void> _submit() async {
    final session = ref.read(multitracksSessionProvider);
    if (session.status == MultiTracksSessionStatus.authenticating) return;
    if (_username.text.trim().isEmpty || _password.text.isEmpty) return;
    await ref.read(multitracksSessionProvider.notifier).signIn(_username.text, _password.text);
    if (!mounted) return;
    if (ref.read(multitracksSessionProvider).isAuthenticated) {
      _password.clear();
      TextInput.finishAutofillContext();
    }
  }

  @override
  Widget build(BuildContext context) {
    final session = ref.watch(multitracksSessionProvider);
    final busy = session.status == MultiTracksSessionStatus.authenticating;
    final expired = session.status == MultiTracksSessionStatus.expired;
    final error = session.status == MultiTracksSessionStatus.failure ? session.error : null;

    return Center(
      child: SingleChildScrollView(
        padding: const EdgeInsets.all(24),
        child: ConstrainedBox(
          constraints: const BoxConstraints(maxWidth: 420),
          child: AutofillGroup(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                const Icon(Icons.cloud_download_outlined, color: kAccent, size: 48),
                const SizedBox(height: 12),
                const Text('Entrar na MultiTracks',
                    textAlign: TextAlign.center, style: TextStyle(color: kText, fontSize: 20, fontWeight: FontWeight.w600)),
                const SizedBox(height: 8),
                const Text(
                  'Use a sua conta MultiTracks para ver as músicas da biblioteca da sua organização e importá-las no WTracks. '
                  'A senha não é guardada no aparelho.',
                  textAlign: TextAlign.center,
                  style: TextStyle(color: kTextDim),
                ),
                const SizedBox(height: 20),
                if (expired) const _Banner(icon: Icons.lock_clock, text: 'A sessão expirou. Entre novamente.'),
                if (error != null)
                  _Banner(
                    key: const Key('multitracks-login-error'),
                    icon: session.deviceLimit ? Icons.devices_other : Icons.error_outline,
                    text: error,
                  ),
                TextField(
                  key: const Key('multitracks-username'),
                  controller: _username,
                  enabled: !busy,
                  autofillHints: const [AutofillHints.username, AutofillHints.email],
                  keyboardType: TextInputType.emailAddress,
                  textInputAction: TextInputAction.next,
                  autocorrect: false,
                  style: const TextStyle(color: kText),
                  decoration: _decoration('Usuário ou e-mail'),
                  onSubmitted: (_) => _passwordFocus.requestFocus(),
                ),
                const SizedBox(height: 12),
                TextField(
                  key: const Key('multitracks-password'),
                  controller: _password,
                  focusNode: _passwordFocus,
                  enabled: !busy,
                  obscureText: _obscure,
                  enableSuggestions: false,
                  autocorrect: false,
                  autofillHints: const [AutofillHints.password],
                  textInputAction: TextInputAction.done,
                  style: const TextStyle(color: kText),
                  decoration: _decoration('Senha').copyWith(
                    suffixIcon: IconButton(
                      tooltip: _obscure ? 'Mostrar senha' : 'Ocultar senha',
                      icon: Icon(_obscure ? Icons.visibility : Icons.visibility_off, color: kTextDim),
                      onPressed: () => setState(() => _obscure = !_obscure),
                    ),
                  ),
                  onSubmitted: (_) => _submit(),
                ),
                const SizedBox(height: 20),
                FilledButton(
                  key: const Key('multitracks-sign-in'),
                  onPressed: busy ? null : _submit,
                  style: FilledButton.styleFrom(minimumSize: const Size.fromHeight(48)),
                  child: busy
                      ? const SizedBox(width: 20, height: 20, child: CircularProgressIndicator(strokeWidth: 2))
                      : const Text('Entrar'),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  InputDecoration _decoration(String label) => InputDecoration(
        labelText: label,
        labelStyle: const TextStyle(color: kTextDim),
        enabledBorder: const OutlineInputBorder(borderSide: BorderSide(color: kBorder)),
        focusedBorder: const OutlineInputBorder(borderSide: BorderSide(color: kAccent)),
        disabledBorder: const OutlineInputBorder(borderSide: BorderSide(color: kBorder)),
        border: const OutlineInputBorder(),
      );
}

class _Banner extends StatelessWidget {
  final IconData icon;
  final String text;
  const _Banner({super.key, required this.icon, required this.text});

  @override
  Widget build(BuildContext context) => Container(
        margin: const EdgeInsets.only(bottom: 16),
        padding: const EdgeInsets.all(12),
        decoration: BoxDecoration(
          color: Colors.redAccent.withValues(alpha: 0.12),
          borderRadius: BorderRadius.circular(8),
          border: Border.all(color: Colors.redAccent.withValues(alpha: 0.5)),
        ),
        child: Row(crossAxisAlignment: CrossAxisAlignment.start, children: [
          Icon(icon, color: Colors.redAccent, size: 20),
          const SizedBox(width: 10),
          Expanded(child: Text(text, style: const TextStyle(color: kText))),
        ]),
      );
}
