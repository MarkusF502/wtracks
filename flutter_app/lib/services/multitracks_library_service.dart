import 'dart:io';

import '../models/multitracks_session.dart';
import 'multitracks_content_provider.dart';
import 'multitracks_contract.dart';

/// HTTP 401/403: a sessão não vale mais. O código de negócio de sessão expirada ainda não foi capturado, então só o
/// status HTTP é tratado assim.
class MultiTracksSessionExpired implements Exception {
  const MultiTracksSessionExpired();
}

/// Resposta com HTTP 200 mas `result`/`errorCode` de erro.
class MultiTracksBusinessFailure implements Exception {
  final int result, errorCode;
  final String? serverMessage;
  const MultiTracksBusinessFailure(this.result, this.errorCode, this.serverMessage);
}

class MultiTracksSongPage {
  final List<MultiTracksSongSummary> songs;
  final int pageNumber, totalRecords;
  final bool hasNextPage;
  const MultiTracksSongPage({required this.songs, required this.pageNumber, required this.totalRecords, required this.hasNextPage});
}

/// `library/songs` da organização padrão, com o corpo validado pela probe (`filter: 1`, `sort: 3`, `sortDirection: 2`).
/// Os significados de filtro/ordenação ainda não foram correlacionados com o app, por isso não são configuráveis.
class MultiTracksLibraryService {
  MultiTracksLibraryService({required this.transport, required this.profile, this.pageSize = 20});

  final MultiTracksJsonTransport transport;
  final MultiTracksClientProfile profile;
  final int pageSize;

  Future<MultiTracksSongPage> songs(MultiTracksLibraryContext context, {required int pageNumber, String search = ''}) async {
    final request = MultiTracksLibraryRequestBuilder(context).songs(pageNumber: pageNumber, pageSize: pageSize, search: search);
    final response = await transport.post(profile, request.route, request.body);
    if (response.statusCode == HttpStatus.unauthorized || response.statusCode == HttpStatus.forbidden) {
      throw const MultiTracksSessionExpired();
    }
    if (response.statusCode != HttpStatus.ok) throw MultiTracksHttpFailure(response.statusCode);
    final envelope = MultiTracksPageEnvelope.fromJson(response.body);
    if (!envelope.isSuccess) {
      throw MultiTracksBusinessFailure(envelope.result, envelope.errorCode, safeServerMessage(response.body['message']));
    }
    final songs = <MultiTracksSongSummary>[];
    for (final item in envelope.data) {
      if (item is! Map) throw const FormatException('Invalid MultiTracks song summary');
      songs.add(MultiTracksSongSummary.fromJson(item.cast<String, Object?>()));
    }
    return MultiTracksSongPage(
      songs: List.unmodifiable(songs),
      pageNumber: envelope.pageNumber,
      totalRecords: envelope.totalRecords,
      hasNextPage: envelope.hasNextPage,
    );
  }
}
