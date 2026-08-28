# Target disc

The project targets the North American PlayStation release of *Final Fantasy
Tactics*, serial `SCUS-94221`.

## Verified identity

| Property | Value |
| --- | --- |
| Input filename | `fft-us-scus-94221.bin` |
| CUE filename | Generated under `build/disc/` |
| Size | 541,315,152 bytes |
| Track layout | One data track, Mode 2/2352 |
| Sectors | 230,151 |
| Disc length | 51:08:51 |
| Volume label | `FINALFANTASYTACTICS` |
| Boot executable | `SCUS_942.21` |
| CRC-32 | `377f6510` |
| MD5 | `b156ba386436d20fd5ed8d37bab6b624` |
| SHA-1 | `2b5d4db3229cdc7bbd0358b95fcba33dddae8bba` |
| SHA-256 | `29e63bb6d2e7b842fe87f7c0ee03b7076681c34bcc47095cca27ec53236bf4f9` |

The size, sector count, CRC-32, MD5, and SHA-1 exactly match
[Redump disc 55](https://redump.info/disc/55), whose dump status is
**Verified**. Redump associates the same disc data with both the Original and
Greatest Hits packaging, so the physical packaging edition cannot be
distinguished from this image alone.

The ISO 9660 primary volume descriptor was also inspected directly. It reports
the `PLAYSTATION` system identifier and `FINALFANTASYTACTICS` volume label. The
disc's `SYSTEM.CNF` boots `cdrom:\\SCUS_942.21;1`.

The SHA-256 value is an additional project-local fingerprint; Redump currently
publishes CRC-32, MD5, and SHA-1 for this track.
