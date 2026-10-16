class MultiTracksLibraryContext {
  const MultiTracksLibraryContext({
    required this.hash,
    required this.customerId,
    required this.userAccessId,
    required this.countryId,
    required this.build,
    required this.restricted,
    required this.language,
    this.siteId,
  });

  final String hash;
  final int customerId;
  final int userAccessId;
  final int countryId;
  final int build;
  final bool restricted;
  final String language;
  final int? siteId;
}

class MultiTracksLibraryRequest {
  const MultiTracksLibraryRequest(this.route, this.body);

  final String route;
  final Map<String, Object?> body;
}

class MultiTracksLibraryRequestBuilder {
  const MultiTracksLibraryRequestBuilder(this.context);

  final MultiTracksLibraryContext context;

  MultiTracksLibraryRequest songs({
    int pageNumber = 1,
    int pageSize = 20,
    String search = '',
    int filter = 1,
  }) {
    return MultiTracksLibraryRequest('library/songs', {
      ..._commonPage(pageNumber, pageSize, search),
      'filter': filter,
      'sort': 3,
      'sortDirection': 2,
      'siteID': _requiredSiteId('library/songs'),
    });
  }

  MultiTracksLibraryRequest artists({
    int pageNumber = 1,
    int pageSize = 20,
    String search = '',
  }) {
    return MultiTracksLibraryRequest('library/artists', {
      ..._commonPage(pageNumber, pageSize, search),
      'purchasedContent': true,
      'sort': 2,
      'sortDirection': 1,
      'siteID': _requiredSiteId('library/artists'),
    });
  }

  MultiTracksLibraryRequest albums({
    int pageNumber = 1,
    int pageSize = 20,
    String search = '',
  }) {
    return MultiTracksLibraryRequest('library/albums', {
      ..._commonPage(pageNumber, pageSize, search),
      'purchasedContent': true,
      'sort': 2,
      'sortDirection': 1,
      'siteID': _requiredSiteId('library/albums'),
    });
  }

  MultiTracksLibraryRequest themes({
    int pageNumber = 1,
    int pageSize = 20,
    String search = '',
  }) {
    return MultiTracksLibraryRequest('library/themes', {
      ..._commonPage(pageNumber, pageSize, search),
      'purchasedContent': true,
      'sortDirection': 1,
    });
  }

  MultiTracksLibraryRequest genres({
    int pageNumber = 1,
    int pageSize = 20,
    String search = '',
  }) {
    return MultiTracksLibraryRequest('library/genres', {
      ..._commonPage(pageNumber, pageSize, search),
      'purchasedContent': true,
      'sortDirection': 1,
    });
  }

  List<MultiTracksLibraryRequest> defaultExploration() => [
    songs(),
    artists(),
    albums(),
    themes(),
    genres(),
  ];

  Map<String, Object?> _commonPage(
    int pageNumber,
    int pageSize,
    String search,
  ) {
    if (pageNumber < 1) {
      throw ArgumentError.value(pageNumber, 'pageNumber', 'must be >= 1');
    }
    if (pageSize < 1) {
      throw ArgumentError.value(pageSize, 'pageSize', 'must be >= 1');
    }
    return {
      'hash': context.hash,
      'customerID': context.customerId,
      'userAccessID': context.userAccessId,
      'countryID': context.countryId,
      'build': context.build,
      'pageNumber': pageNumber,
      'pageSize': pageSize,
      'restricted': context.restricted,
      'language': context.language,
      'search': search,
    };
  }

  int _requiredSiteId(String route) {
    final siteId = context.siteId;
    if (siteId == null) {
      throw StateError('$route requires siteID');
    }
    return siteId;
  }
}

class MultiTracksContentSelection {
  const MultiTracksContentSelection({
    required this.contentId,
    required this.contentType,
    required this.keyId,
    this.midiBankId = 0,
    this.demoSetlistSongId = 0,
  });

  final int contentId;
  final int contentType;
  final int keyId;
  final int midiBankId;
  final int demoSetlistSongId;
}

class MultiTracksContentRequestBuilder {
  const MultiTracksContentRequestBuilder(this.context);

  final MultiTracksLibraryContext context;

  MultiTracksLibraryRequest metadata(MultiTracksContentSelection selection) {
    return MultiTracksLibraryRequest('content/download', {
      ..._common(),
      'items': [
        _item(
          selection,
          downloadLink: false,
          redeemRental: false,
          includeRedemptionId: false,
        ),
      ],
    });
  }

  MultiTracksLibraryRequest downloadLink(
    MultiTracksContentSelection selection,
  ) {
    return MultiTracksLibraryRequest('content/download', {
      ..._common(),
      'items': [
        _item(
          selection,
          downloadLink: true,
          redeemRental: false,
          includeRedemptionId: true,
        ),
      ],
    });
  }

  MultiTracksLibraryRequest redeemRental(
    MultiTracksContentSelection selection,
  ) {
    return MultiTracksLibraryRequest('content/download', {
      ..._common(),
      'items': [
        _item(
          selection,
          downloadLink: true,
          redeemRental: true,
          includeRedemptionId: true,
        ),
      ],
    });
  }

  Map<String, Object?> _common() => {
    'hash': context.hash,
    'customerID': context.customerId,
    'userAccessID': context.userAccessId,
    'language': context.language,
    'countryID': context.countryId,
    'build': context.build,
    'restricted': context.restricted,
  };

  Map<String, Object?> _item(
    MultiTracksContentSelection selection, {
    required bool downloadLink,
    required bool redeemRental,
    required bool includeRedemptionId,
  }) => {
    'contentID': selection.contentId,
    'contentType': selection.contentType,
    'metadata': true,
    if (includeRedemptionId) 'redemptionID': 0,
    'keyID': selection.keyId,
    'midiBankID': selection.midiBankId,
    'demoSetlistSongID': selection.demoSetlistSongId,
    'redeemPreview': false,
    'downloadLink': downloadLink,
    'redeemRental': redeemRental,
  };
}

class MultiTracksContentResponse {
  const MultiTracksContentResponse({
    required this.items,
    required this.result,
    required this.errorCode,
    this.rentalsRemaining,
    this.rentalsPreviews,
  });

  factory MultiTracksContentResponse.fromJson(Map<String, Object?> json) {
    final data = json['data'];
    final result = json['result'];
    final errorCode = json['errorCode'];
    if (data is! Map || result is! int || errorCode is! int) {
      throw const FormatException('Invalid MultiTracks content response');
    }
    final typedData = data.cast<String, Object?>();
    final rawItems = typedData['items'];
    final rentalsRemaining = typedData['rentalsRemaining'];
    final rentalsPreviews = typedData['rentalsPreviews'];
    if (rawItems is! List ||
        (rentalsRemaining != null && rentalsRemaining is! int) ||
        (rentalsPreviews != null && rentalsPreviews is! int)) {
      throw const FormatException('Invalid MultiTracks content data');
    }
    return MultiTracksContentResponse(
      items: List<MultiTracksContentItem>.unmodifiable(
        rawItems.map((item) {
          if (item is! Map) {
            throw const FormatException('Invalid MultiTracks content item');
          }
          return MultiTracksContentItem.fromJson(item.cast<String, Object?>());
        }),
      ),
      result: result,
      errorCode: errorCode,
      rentalsRemaining: rentalsRemaining as int?,
      rentalsPreviews: rentalsPreviews as int?,
    );
  }

  final List<MultiTracksContentItem> items;
  final int result;
  final int errorCode;
  final int? rentalsRemaining;
  final int? rentalsPreviews;

  bool get isSuccess => result == 1 && errorCode == 0;
}

class MultiTracksContentItem {
  const MultiTracksContentItem({
    required this.raw,
    required this.contentId,
    required this.libraryId,
    required this.title,
    required this.downloadUrl,
    required this.fileSize,
    required this.contentStatus,
    required this.songStatus,
    required this.playOfTheWeek,
    required this.stems,
  });

  factory MultiTracksContentItem.fromJson(Map<String, Object?> json) {
    T? optional<T>(String key) {
      final value = json[key];
      if (value == null) return null;
      if (value is! T) {
        throw FormatException('Invalid MultiTracks content field: $key');
      }
      return value as T;
    }

    final rawStems = json['stems'];
    if (rawStems != null && rawStems is! List) {
      throw const FormatException('Invalid MultiTracks stems');
    }
    final stems = rawStems == null
        ? const <MultiTracksStemDescriptor>[]
        : List<MultiTracksStemDescriptor>.unmodifiable(
            (rawStems as List).map((stem) {
              if (stem is! Map) {
                throw const FormatException('Invalid MultiTracks stem');
              }
              return MultiTracksStemDescriptor.fromJson(
                stem.cast<String, Object?>(),
              );
            }),
          );
    return MultiTracksContentItem(
      raw: Map<String, Object?>.unmodifiable(json),
      contentId: optional<int>('contentID'),
      libraryId: optional<int>('libraryID'),
      title: optional<String>('title'),
      downloadUrl: optional<String>('downloadUrl'),
      fileSize: optional<int>('fileSize'),
      contentStatus: optional<int>('contentStatus'),
      songStatus: optional<int>('songStatus'),
      playOfTheWeek: optional<bool>('playOfTheWeek'),
      stems: stems,
    );
  }

  final Map<String, Object?> raw;
  final int? contentId;
  final int? libraryId;
  final String? title;
  final String? downloadUrl;
  final int? fileSize;
  final int? contentStatus;
  final int? songStatus;
  final bool? playOfTheWeek;
  final List<MultiTracksStemDescriptor> stems;
}

class MultiTracksStemDescriptor {
  const MultiTracksStemDescriptor({
    required this.contentType,
    required this.stemId,
    required this.partId,
    required this.keyId,
    required this.range,
    required this.part,
    required this.abbreviation,
    required this.anyKey,
    required this.clickOrGuide,
    required this.vocal,
    required this.order,
  });

  factory MultiTracksStemDescriptor.fromJson(Map<String, Object?> json) {
    final contentType = json['contentType'];
    final stemId = json['stemID'];
    final partId = json['partID'];
    final keyId = json['keyID'];
    final range = json['range'];
    final part = json['part'];
    final abbreviation = json['abbreviation'];
    final anyKey = json['anyKey'];
    final clickOrGuide = json['clickOrGuide'];
    final vocal = json['vocal'];
    final order = json['order'];
    if (contentType is! int ||
        stemId is! int ||
        partId is! int ||
        keyId is! int ||
        range is! int ||
        part is! String ||
        abbreviation is! String ||
        anyKey is! bool ||
        clickOrGuide is! bool ||
        vocal is! bool ||
        order is! int) {
      throw const FormatException('Invalid MultiTracks stem descriptor');
    }
    return MultiTracksStemDescriptor(
      contentType: contentType,
      stemId: stemId,
      partId: partId,
      keyId: keyId,
      range: range,
      part: part,
      abbreviation: abbreviation,
      anyKey: anyKey,
      clickOrGuide: clickOrGuide,
      vocal: vocal,
      order: order,
    );
  }

  final int contentType;
  final int stemId;
  final int partId;
  final int keyId;
  final int range;
  final String part;
  final String abbreviation;
  final bool anyKey;
  final bool clickOrGuide;
  final bool vocal;
  final int order;
}

class MultiTracksPageEnvelope {
  const MultiTracksPageEnvelope({
    required this.data,
    required this.pageNumber,
    required this.totalPages,
    required this.totalRecords,
    required this.result,
    required this.errorCode,
  });

  factory MultiTracksPageEnvelope.fromJson(Map<String, Object?> json) {
    final data = json['data'];
    final pageNumber = json['pageNumber'];
    final totalPages = json['totalPages'];
    final totalRecords = json['totalRecords'];
    final result = json['result'];
    final errorCode = json['errorCode'];
    if (data is! List ||
        pageNumber is! int ||
        totalPages is! int ||
        totalRecords is! int ||
        result is! int ||
        errorCode is! int) {
      throw const FormatException('Invalid MultiTracks page envelope');
    }
    return MultiTracksPageEnvelope(
      data: List<Object?>.unmodifiable(data),
      pageNumber: pageNumber,
      totalPages: totalPages,
      totalRecords: totalRecords,
      result: result,
      errorCode: errorCode,
    );
  }

  final List<Object?> data;
  final int pageNumber;
  final int totalPages;
  final int totalRecords;
  final int result;
  final int errorCode;

  bool get isSuccess => result == 1 && errorCode == 0;

  bool get hasNextPage =>
      data.isNotEmpty && totalPages > 0 && pageNumber < totalPages;
}

class MultiTracksSongSummary {
  const MultiTracksSongSummary({
    required this.libraryId,
    required this.songId,
    required this.song,
    required this.songStatus,
    required this.artistId,
    required this.artist,
    required this.albumId,
    required this.album,
    required this.image,
    required this.image2x,
    required this.previewUrl,
    required this.dateContentPurchased,
    required this.rentalsAvailable,
    required this.cloudSong,
  });

  factory MultiTracksSongSummary.fromJson(Map<String, Object?> json) {
    final libraryId = json['libraryID'];
    final songId = json['songID'];
    final song = json['song'];
    final songStatus = json['songStatus'];
    final artistId = json['artistID'];
    final artist = json['artist'];
    final albumId = json['albumID'];
    final album = json['album'];
    final image = json['image'];
    final image2x = json['image2x'];
    final previewUrl = json['previewUrl'];
    final dateContentPurchased = json['dateContentPurchased'];
    final rentalsAvailable = json['rentalsAvailable'];
    final cloudSong = json['cloudSong'];
    if (libraryId is! int ||
        songId is! int ||
        song is! String ||
        songStatus is! int ||
        artistId is! int ||
        artist is! String ||
        albumId is! int ||
        album is! String ||
        image is! String ||
        image2x is! String ||
        previewUrl is! String ||
        (dateContentPurchased != null && dateContentPurchased is! String) ||
        rentalsAvailable is! bool ||
        cloudSong is! bool) {
      throw const FormatException('Invalid MultiTracks song summary');
    }
    return MultiTracksSongSummary(
      libraryId: libraryId,
      songId: songId,
      song: song,
      songStatus: songStatus,
      artistId: artistId,
      artist: artist,
      albumId: albumId,
      album: album,
      image: image,
      image2x: image2x,
      previewUrl: previewUrl,
      dateContentPurchased: dateContentPurchased as String?,
      rentalsAvailable: rentalsAvailable,
      cloudSong: cloudSong,
    );
  }

  final int libraryId;
  final int songId;
  final String song;
  final int songStatus;
  final int artistId;
  final String artist;
  final int albumId;
  final String album;
  final String image;
  final String image2x;
  final String previewUrl;
  final String? dateContentPurchased;
  final bool rentalsAvailable;
  final bool cloudSong;
}
