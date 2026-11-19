# Source provenance

The progress report distinguishes independently recovered game C (`exact`) from
strictly verified library C imported from an existing public decompilation
(`donor`). Donor provenance is retained in the `outcome`, `how`, and `source`
columns of `MATCHED.tsv`; it is not relabelled as original work in this
repository.

Every published donor function was independently compiled with its recorded
recipe, compared against the Wheel of Fortune ROM at its target address, and
included in the byte-identical cartridge relink. Sharing a likely library name
or implementation is not enough to receive progress credit.

| Source corpus | Functions | Owned code bytes |
|---|---:|---:|
| BattleTanx | 199 | 46,688 |
| N64 SDK/libultra reconstruction (`sdk_2_0F_libultra_rom`) | 73 | 18,400 |
| Madden 64 | 16 | 5,032 |
| Rugrats 64 | 5 | 80 |
| Nagano Winter Olympics '98 | 4 | 224 |
| **Verified donor C total** | **297** | **70,424** |

Four additional donor routines contain assembly implementations and therefore
do not receive matching-C or linked-C progress credit. They remain classified
as `donor-assembly` in `progress-inventory.tsv`.

The copied function files preserve the exact source text used for verification.
Project-specific licensing and attribution should be consulted before
redistributing these sources outside this decompilation repository.

