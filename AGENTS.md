# Wheel of Fortune (N64, USA): agent guide

Reconstruct the original source so the original compiler, with the original flags, emits object code that matches
the retail ROM byte for byte, function by function. Correct structure outranks any score: types, ownership,
storage, control flow, unit boundaries and referents.

The point of the project is source a reader can understand. Matching bytes prove the source is faithful; they
don't make it readable. Every function must pass the reader test of the `decomp-code-rules` skill: would a
programmer on the original team have typed this? Source that matches through tricks (a fakematch) is not a match.

**Only the tools' printed results count.** The upstream ledgers and documents (`README.md`, `MATCHED.tsv`,
`progress-*.tsv`, `source-accounted.tsv`, `RELINK.json`, `CARTRIDGE.json`, `docs/`, `proofs/`) are claims made by
an earlier toolchain that is not in this repository. They are neither inputs nor maintained. Never quote a number
from them.

## Project adapter

Everything runs through `./wof` at the repository root. From a Windows shell it re-enters WSL (`Ubuntu`), where
the compiler lives; from PowerShell use `wsl -d Ubuntu -- sh /mnt/e/<checkout>/wof <command>`.

| verb | this project's command |
|---|---|
| `build` / `gate` | `./wof gate` (always a clean compile of every unit; about 10 seconds) |
| `match <unit>` | `./wof match UNIT...` |
| `diff <function>` | `./wof diff UNIT` (left: retail, right: built) |
| `report` | `./wof report` (the gate's result, then both score numbers) |
| `rules [<unit>]` | `./wof rules [-v] [UNIT...]` |
| `disasm` | `./wof diff UNIT`; for ranges outside a unit, `mips-linux-gnu-objdump -D -b binary -m mips:4300 -EB` on the ROM |
| symbol proposals | `./wof infer` (not a gate: it reads addresses from retail and writes proposals to the build directory) |
| unit boundaries | `./wof unitmap [-v]` (not a gate: prints the evidence for original object boundaries among the game functions, from the ROM and the last gate's unit list; `-v` adds the strings each function uses) |
| `permute` | none |

- **Toolchain.** Two compilers, both inside WSL and outside the repository: GCC 2.7.2 for MIPS (`gcc`, `cc1`,
  `as` 2.6) in `$WOF_TOOLCHAIN`, default `~/wof/gcc272`, for the game and libgcc; IDO 5.3 in `$WOF_IDO`, default
  `~/wof/ido53`, for libultra. Host tools need `cc` and `mips-linux-gnu-objdump` in WSL. Build output goes to
  `~/wof/build/<checkout id>` in WSL, outside the repository; the wrapper prints nothing about it, tools print
  the paths they write.
- **ROM.** Any byte order; the tools swap it in memory and refuse a ROM whose SHA-1 is not
  `b51b28660699bf029f862f51c319a5962fe9de9b`. A git worktree uses the main checkout's ROM. The ROM is never
  committed.
- **Flag classes** (`config/flags.tsv`: class, assembler, flags):
  - `game`: `-O0 -g -G0 -mips3 -mgp32 -mfp32`, assembler `asn64`;
  - `libgcc_*`: `-O2 -G0 -mips3 -mgp32 -mfp32 -DL_<function>`, assembler `asn64`, one class per libgcc function;
  - `ultra_*`: IDO 5.3 (`ido`), `-mips2 -o32 -non_shared -G 0 -Wab,-r4300_mul -DNDEBUG -D_FINALROM`: `-O1` for
    `os/` and `io/`, `-O3` for `audio/`, `gu/`, `libc/` and `sched/`, with the per-file exceptions the table
    records (`ll.c`, the assembly sources, `exceptasm`);
  - `asm`: GNU as, for the entry stub.
- **Include paths.** The 32-bit preprocessors cannot `#include` from the Windows mount. `include/` and `lib/`
  are copied into the build directory on every run, and the flag rows name them there
  (`-I $WOF_BUILD/include`, `-I $WOF_BUILD/lib/...`). Sources under `lib/` are compiled from that copy.
- **The `asn64` assembler mode.** The game's objects were not assembled by GNU as. `tools/asn64.c` rewrites cc1's
  assembly into the forms retail shows (no delay-slot filling, `$at` for symbol-plus-register loads, literal-pool
  float constants, and so on; the file's header lists every rule) and GNU as assembles the result. Each rule was
  derived from retail and is validated by every unit in the gate. A new rule needs the same evidence: a retail
  shape that no source change explains, seen in more than one function. Run the full gate after any change to it.
- **Units** (`config/units.tsv`: unit, address, size, state, flag class, source, optional entry symbol). A unit is
  one compiled source file placed at one address: by its `.text`, or, for an object without code (a table, a
  block of uninitialised data), by its first data section. `match` units are in the gate; `open` units are compiled and
  compared but keep retail's bytes in the linked image. **`open` is the parking mechanism**: an unfinished
  function stays in its own `open` unit. Today nearly every unit holds one function, which is not the original
  layout (see "Unit boundaries").
- **Functions** (`config/functions.tsv`): the inventory of 773 function ranges, 745 C and 28 assembly. The
  assembly ranges are the entry stub and libultra's own `.s` sources: `ORIGINAL-ASM`.
- **Symbols** (`config/symbols.txt`): addresses of names no unit defines yet; empty today. `func_XXXXXXXX` and `D_XXXXXXXX`
  carry their address in the name and need no entry. A unit that defines a global exports it to every other
  unit. The gate rejects an undeclared name, a name bound to two addresses, and an address-named function placed
  anywhere else.
- **Reference sources.** libultra is the decompals `ultralib` reconstruction under `lib/ultralib`
  (`PROVENANCE.tsv` lists each file as verbatim or modified). Retail links an IDO-built `libultra_rom` older than
  2.0I; the version letter is an inference, built as `VERSION_H`, and each pre-2.0I form sits in a
  `BUILD_VERSION` conditional beside the newer code. Library sources stay verbatim to upstream otherwise: do not
  edit them to satisfy the rule checker. libgcc (`lib/libgcc`) is a reconstruction of three GCC 2.7.2 functions
  whose provenance file says what it was written after. The MPEG player (the 82 functions at 0x800887D8..0x800A5074) descends from the
  Berkeley `mpeg_play` decoder, whose source is published: lineage evidence for its functions, types and macros,
  adopted only where the bytes agree and marked `guess:` where the binary itself holds no name.
- **Policies.** Running the game is not needed. A decompiler may be used as a reading aid; its output is never
  source. Commit messages name the change (`match: reconstruct func_80002348`, `tools: verify relocation
  targets`).
- **Tooling language.** Write project tooling in C (see `tools/`). Avoid Python: it is not part of the build, the
  gate or the rule checker, and new tools must not need it.

## Objective and scores

- The goal is an exact match for every function: identical instructions, constants and *ordered relocation
  targets*. The gate resolves every relocation, so a matching body that calls the wrong function or names the
  wrong global fails.
- Progress is two numbers, both printed by `./wof report`:
  - **matched under the rules** (the headline): byte-identical at the gate *and* passing every [match] rule;
  - **bytes matched**: byte-identical at the gate.
- `MATCH-PENDING` functions (byte-identical, failing a [match] rule) are open work, not progress.
- The 28 assembly ranges are `ORIGINAL-ASM`: byte-identical at the gate, listed apart (`kind` `asm` in
  `config/functions.tsv`) and counted neither way.

## Workflow

1. **Pick work.** `MATCH-PENDING` functions, `open` units, a unit close to complete.
2. **Classify the gap** (`wall-identifier`): referent, then inline/call set, then control flow, then
   register/schedule. Fix the earliest class that still differs. This is `-O0` code: almost every difference is
   a source-shape difference (types, statement order, loop form, declaration order), not a scheduling one.
3. **Reconstruct** with `matcher`; recover hidden helpers with `helper-recovery`.
4. **Iterate** with `./wof match`. Run `./wof gate` when a change spans units, for example a shared-header edit.
5. **Gate** before committing or merging. The gate must stay green.

## The byte gate

A function is done when **the whole image, linked with that function compiled from source, still hashes to the
retail ROM's hash**. `./wof gate` compiles every unit from scratch, resolves relocations, zeroes each claimed
unit's range in a copy of the ROM, writes the compiled bytes in, and compares the SHA-1.

- The gate has two states, `GATE OK` or `GATE FAILED`. Write "matched" or "banked" only from its printed lines.
- It is green at 0%: read the coverage it prints (`N units, T text + D data bytes from source`).
- A red gate names the units that differ; `./wof diff UNIT` shows where.
- A unit's read-only data (jump tables, float literals) is placed where retail's instructions point and compared
  too. A data section that nothing references or declares has no address and fails.
- It is blind to honesty of the source. That is the rule checker's job.

## Code rules

The full catalogue is the user-level `decomp-code-rules` skill (`references/rules.md`). Two laws apply always:

1. **The bytes win.** A change made for style must not change what the compiler emits. When a rule and the bytes
   disagree, keep the bytes and write `// RULE-EXCEPTION: <rule>, <reason the bytes give>` at the code.
2. **Identical bytes alone are not a match.** A function counts as matched only when its bytes match *and* it
   passes every **[match]** rule:
   - R1: each type declared once, in a shared header;
   - R2: each global declared once, as `extern` in a header, and defined in its owning unit;
   - R4: no fixed-offset casts;
   - R17: no fake code (probes, `volatile` carriers, dummy locals, steering blocks);
   - R18: no assembly bodies.

   R13 (vtables) does not apply: the game is C.

`./wof rules` implements the rows (`tools/rules.c`). What it flags as [match]:

| rule | row |
|---|---|
| R1 | a type name defined in more than one file, with the same body or a different one |
| R2 | an `extern` of a global in a `.c` file; one global declared with different types |
| R4 | a constant added to a `(char *)`/`(u8 *)` cast |
| R17 | a local nothing uses (unless its line carries `NOTE:`, `BUG:`, `guess:` or `RULE-EXCEPTION`); `volatile` in a function body; an empty `if`/`else` block; a bare `;`; `do { } while (0)` in a body; self-assignment; `+ 0`; `* 1`; a `pad` member |
| R18 | `__asm__`, `asm` |

The checker judges only what a unit compiles: the gate leaves each unit's preprocessor output beside its
object, and an `#if` branch none of whose lines reaches that output is neither judged nor counted. Run
`./wof gate` (or `./wof report`) before `./wof rules`.

Advisory, not blocking: placeholder names (R7), prototypes in source files (R25), missing header comments (R33),
dereferenced casts of `expression + constant`.

Project profile:

| item | this project |
|---|---|
| compiler dialect (R22) | GNU C 2.7.2: C89 plus GNU extensions. Declarations at the top of a block. The compiler accepts `//` comments; whether the original team wrote them is unknown. No C99 (`for` declarations, `stdint.h`, designated initializers work only as GNU 2.7 allows). |
| naming style (R8) | **Game code (the user's ruling):** Table 1 of `style-defaults.md`, the C engine style, except for function names (below): `prefix_topic.c` units, `lowerCamel_t` struct and enum types, `lowerCamel` members, locals and parameters, `UPPER_SNAKE` constants and enum values. The style is a default and gives way to evidence (R7, R8). **The binary records some original function names** in its message strings (`AllocProc`, `GetProcBefore`, `CreatProc`, `ProcPostMessage`, `DrawObjs`, `InitMainFlash`, `SwitchImage`, `CheckPercentDone`): those are kept verbatim, misspellings included, and they show the original wrote plain `VerbNoun` function names with no `Prefix_`, the subsystem's noun inside the name (`ProcPostMessage`, `AllocObj`). **Invented function names follow that recorded form (the user's ruling), not the default's `Prefix_VerbNoun`**, and are recorded as invented. **libultra and libgcc: the SDK's and GCC's own names and style, verbatim.** Renames cross units: only a naming lane renames, and a placeholder stays a placeholder until the thing's purpose is known. |
| layout style (R23, R32, R33) | Game code (the user's ruling): K&R braces as `if ( cond ) {`, 4-space indent, 100 columns, C89 declarations at the top of the block, the `/*` `=====` `Name` *description* `=====` `*/` function banner, `// unit.c -- purpose` unit openings. libultra keeps its own. Layout is [checked] here (see the line-information row). |
| placeholder patterns (R7) | `func_XXXXXXXX`, `D_XXXXXXXX`, `spXX`, `argN`, `unk_XX`, `mXX` members, `padN`, `tempN`, `varN`, `n64dk_*` |
| evidence for names (R7) | Message strings that start with a function name (`"AllocProc: Out of Procs"`) name the function that prints them, and sometimes its data (`"Reached end of procst."`); `./wof unitmap -v` lists them per function. The 22 RCS `$Revision` strings mark original objects. libultra and libgcc names come from the SDK; the MPEG player's from `mpeg_play`, as `guess:`. Everything else is invented and recorded as invented. |
| does the binary record source lines? | The ROM has no line table, but **layout is [checked] all the same.** The game was built with `-g`, and under `-g` cc1 2.7.2 writes a placeholder `nop` before a loop that follows a label unless a line-number note separates them. So whether a `for`/`while`/`do` starts on a new source line changes the code. Gate every formatting change. |
| parking mechanism | the `open` state in `config/units.tsv` |
| rules tightened or relaxed | **R1 tightened:** an identical duplicate of a type in two files fires, not only a differing one. Reason: the imported sources have no headers at all, and 438 files re-typedef the same scalar types; those copies are the R1 violation in its plainest form. **R2 and R17 relaxed for `lib/ultralib` only (the user's ruling):** an `extern` in a `.c` file and a local nothing uses do not fire there. Reason: that tree is the SDK's source kept verbatim to upstream, and the SDK's own code declares `extern`s inside `.c` files and leaves locals unused; editing it to satisfy the checker would trade a faithful copy for a private fork. One global declared with two types still fires there, and so does every other R17 row. Game code and `lib/libgcc` get no relaxation. |

## Matching rules that are easy to get wrong

- **Levers are disposable experiments.** Never keep probes, unused declarations, fake locals, padding or
  distorted source to move a score. A trick that closes a gap is a clue to the real source.
- **An unused local is a claim.** At `-O0` every local gets a stack slot, so a hole in the frame is evidence of
  *something*: a local of a nested block, a larger array or struct, a variable the original really never used.
  `pad0` says none of those. Find which one it is. A local kept as genuinely unused carries a
  `/* NOTE: unused in the original */` on its line, after the alternatives were tried.
- **Locals that are really one struct.** Consecutive `spXX` scalars whose address is passed to a function are
  one struct or array.
- **Prefer original spellings.** A macro or inline helper is more likely the original spelling than a
  hand-expanded body.
- **Keep every exact match, and count it honestly.** A style rule the bytes defeat gets a `RULE-EXCEPTION` and
  counts. A [match] rule makes the function `MATCH-PENDING`: keep its source and list it as open work.

## Source rules

- **One type, one definition**, in a shared header. No unit-local copies or layout views.
- **Each function and global lives in its evidence-backed owner** unit and header. No scattered `extern`s.
- **Access goes through typed members.** A cast is usually a symptom: retype the member or parameter until it
  disappears. A parameter typed `s32` that is dereferenced is a pointer.
- **Unclear identity: chase the evidence** (callers, storage, callees, offsets). If it is still unclear, keep
  the placeholder. Never fabricate.
- **Use the SDK's real headers** for libultra types and functions instead of hand-rolled declarations.
- **No fake code**, storage, labels, aliases or padding to improve a score or the final layout.

## Unit boundaries

The imported tree has one function per file. The original did not: retail pads `.text` to 8 bytes between
objects, and each original object's literals and jump tables sit together in read-only data. A unit is merged
from its functions only on that evidence (R15), and the merged unit must pass the gate with its data section at
one consistent address.

## Data

- A datum gets a real definition in its owning unit once that unit's data range is known. Until then it is an
  `extern` in a header.
- Compiler-generated data (jump tables, float literals) belongs to the unit that emits it.

## Tests and verification

- Matching work runs no test suites: the gate is the verification.
- Tooling changes run the full gate and `./wof rules`; a tooling change that alters either result says so in
  its commit message.
- Claim "matched" only from the tools' printed results.

## Repository hygiene

- Tool inputs go in `config/`, generated output in the build directory, history in version control. Docs
  describe current usage and contracts only: no diaries, score snapshots or campaign logs.
- Source comments explain the code (R21): `RULE-EXCEPTION`s, quirk labels (R36), banners, why a block exists.
  No history, scores, dates or campaign notes.
- Stage only your own unit of work, and never commit build state.
