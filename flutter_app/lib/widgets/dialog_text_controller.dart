import 'package:flutter/material.dart';

/// Owns a dialog's text controller until its exit animation has finished.
/// showDialog's Future completes on pop, before the dialog is unmounted.
class DialogTextController extends StatefulWidget {
  final String initialText;
  final Widget Function(TextEditingController controller) builder;

  const DialogTextController({
    super.key,
    this.initialText = '',
    required this.builder,
  });

  @override
  State<DialogTextController> createState() => _DialogTextControllerState();
}

class _DialogTextControllerState extends State<DialogTextController> {
  late final _controller = TextEditingController(text: widget.initialText);

  @override
  Widget build(BuildContext context) => widget.builder(_controller);

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }
}
