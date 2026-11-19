# Response to the source-quality review (2026-11-19)

This cleanup is integrated in the repository. Per-file results are recorded in
[`cleanup-result.tsv`](cleanup-result.tsv); the exact whole-program evidence is
[`RELINK.json`](../RELINK.json) and [`CARTRIDGE.json`](../CARTRIDGE.json).

## What was true and what was done

The review was right about readability and types, and wrong that the code did not match or that the
header's macros broke logic (none of the risky macros was used in any function body).

All 442 machine-translated files were changed. 422 were cleaned by hand-style rewriting, each kept only
if it still compiled to the same bytes; the other 20 had only the pasted header removed.

| Issue raised | Files before | Files after |
| --- | --- | --- |
| Pasted compatibility header (`N64DK_M2C_PRELUDE`) | 442 | 0 |
| Any `M2C_` macro or type | 442 | 8 |
| Address of a global cast to `s32` | 241 | 119 |
| Empty prototypes (`func_X();`) | 333 | 90 |
| `for (;;) {` scaffolding | 219 | 37 |
| Helper structs (`struct gd_...`) | 230 | 7 |

By file: 348 fully cleaned, 65 partly, and 9 already clean. The result table says what remains in each.

## Verification

- Each of the 422 cleaned files was re-checked after collection: compiled bytes equal, relocations masked.
- The whole cartridge was relinked from the new sources: SHA-1 matches, 0 differing bytes, and 618 of 618
  units linked identically.
- The progress numbers do not change: 750 of 775 functions, 396,752 bytes of matching C.

## What remains, and why

- **Parameters still typed `s32` that are really pointers.** A function's own signature was frozen in
  this pass because other files copy it as their prototype. That is the cause of most remaining
  `s32` casts and of the 65 "partial" files. Fixing it is one coordinated pass over callers and callees.
- **Forms that must stay to keep the bytes** (this is `-O0` code): some loops only match as `while` or
  as `for (;;)`, a few dead `return`/`break` statements and empty `else` branches are needed, 8 gotos
  remain, and two callees stay unprototyped because the original called them without a prototype.
- **Unused locals** that hold the stack layout cannot be removed.
- **No SDK names yet.** `func_8003E318` is very likely `osRecvMesg`; naming libultra functions needs the
  symbol table changed across the project, not just these files.
- **No shared headers.** Every file is still self-contained, so the same struct may be declared in
  several files with different names.

## Review status

The cleanup was produced by automated agents and retained only after exact recompilation checks; it was
not a line-by-line human review. The repository therefore describes these files as cleaned and
byte-verified machine-generated C, not as fully reviewed or portable C.
