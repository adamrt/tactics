# Matching cookbook

Techniques that have actually flipped a near-miss to `matching WIP:` on this
project, collected from the parallel reconstruction workers. Each entry is a
symptom you can see in the diff, followed by the source change that fixes it.

Nothing here is a guess: every trick below was confirmed by a byte-exact match
after applying it. When a trick stops working, delete it rather than qualifying
it — a cookbook of maybes is worse than a short one.

The live worker prompt (`scripts/worker_prompt_fast.txt`) embeds this list.

## HIGH-LEVERAGE TRICKS (from prior workers — use these first)

1. **Look for a TWIN.** The event overlays (bunit/equip/card/require/debugchr/attack/option/jobstts) contain many byte-identical or near-identical siblings. Before drafting from scratch, grep `src/event/` for a function with the same shape:
   ```
   grep -l "SetPolyFT4\|addPrim\|GetTPage" src/event/*.c | head -20
   ```
   If you find a twin, copy it, rename the symbol + externs to this overlay's addresses, and diff. This matched first-try 3+ times for prior workers.

2. **libgpu `addPrim` needs a P_TAG bitfield**, not hand-written masks:
   ```c
   typedef struct { u32 addr:24; u32 len:8; } P_TAG;
   ((P_TAG *)prim)->addr = ot[i];
   ((P_TAG *)&ot[i])->addr = (u32)prim;
   ```

3. **Unexplained larger target stack frame** = unreferenced locals in the original source. Add a dummy `s32 unused[N];` (address-taken if needed) to reach the right frame size. Outgoing-arg area is often 0x18, not 0x10.

4. **`while (n-- != 0)`** must be written `n -= 1; while (n != -1) { ...; n -= 1; }` to get the compare-against-hoisted--1 form.

5. **Relocatable externs get `addiu`; literal `(T*)0x8...` constants get `ori`.** If the target has `addiu`, declare a real extern symbol and put it in the `.ld`.

6. **`u8 *p = &GLOBAL; *p += N;`** (via a local pointer) reuses one lui/addiu base — `GLOBAL += N;` does not.

7. **`s32` locals, not `s16`/`u8`** — avoids spurious `sll`/`sra` sign-extension pairs.

8. Always redirect stdin: `make wip ... </dev/null` (shell loops fail spuriously otherwise).

9. Transient `parse error at end of input` / truncated `.i` is a concurrent-worker race — retry the identical command after ~2-3s.


10. **WLDCORE / OPEN need the ASPSX 2.21 profile.** If the target keeps an
    indexed global address in `$at` across four instructions:
    ```
    lui $at,%hi(sym) ; addiu $at,$at,%lo(sym) ; addu $at,$at,$idx ; load rd,0($at)
    ```
    and your build folds it to three (`lui / addu / load %lo(...)`), that is an
    ASSEMBLER VERSION difference, not a source problem. `WORLD/WLDCORE.BIN` and
    `OPEN/OPEN.BIN` were built with ASPSX < 2.30. Do NOT try to fix it in C — the
    target uses `$at`, which no compiler will allocate.

    Add `PROFILE=gcc-2.6.3_O2_aspsx-2.21` to your make wip commands:
    ```
    make wip ACTION=diff TARGET=... OFFSET=... BYTES=... PROFILE=gcc-2.6.3_O2_aspsx-2.21 </dev/null
    ```
    and pass `--profile gcc-2.6.3_O2_aspsx-2.21` to `scripts/promote_wip.py`.

    It is a PER-FUNCTION exception: some WLDCORE/OPEN functions have no indexed
    global access and match under the canonical 2.34 profile. Try 2.34 first; if
    the diff shows the folded 3-instruction form where the target has 4, retry
    with 2.21. Do not use 2.21 for battle/world/event modules — they were built
    with 2.34.

## Report (under 300 words)
- PROMOTED count + symbols
- SKIPPED (permuter/asm/other) counts
- No verbose explanations — quantity over depth.

Your batch number is: {BATCH_NUM}

## Register allocation and constant materialization

- **`g_ai_data_base` (0x8019f3c4, byte array).** Naming it directly emits
  `lui $at` + `%lo`; going through a local `u8 *base = g_ai_data_base` emits an
  `s0`-relative access. The target mixes both forms, so picking the wrong one is
  a common mismatch. For a global that is written *twice*, use a distinct scalar
  extern (e.g. `D_801A007E`) or GCC will CSE the address into one register where
  the target keeps two.

- **Unexplained `sltiu rd,rd,1` tail** where the target branches instead: GCC
  merged two constant returns into a boolean. Break it up with a `goto` to a
  duplicated `return 0;`.

- **GCC re-materializes an argument constant that the target keeps live**: try
  declaring the callee with *fewer* parameters. A trailing `a2=1` is often a
  leftover live value from the caller, not an argument.

- **A store the target sinks into a load-shadow or branch-delay slot** usually
  means the source read the *next* global into a local before the store. Hoist
  the read above the store.

- **`(s16)` casts on an `s32` local** reproduce `sll`/`sra` into a scratch
  register. Declaring the local as `s16` instead sign-extends *in place* and
  clobbers the source register — not the same code.

- **An if/else chain that should be a `switch`.** GCC 2.6.3 emits a different
  comparison order for the two; if the target's compares are in source order
  with no reassociation, it was a `switch`.

## What not to reconstruct

Some wiki "routines" are not independently compilable functions. Confirm by
disassembly and add them to `config/skip-addresses.txt` (with a reason) rather
than leaving them to be re-issued to the next worker:

- **Tail fragments**: no prologue, read callee-saved registers and stack slots
  they never write, end in a bare `j` to the next label.
- **Data**: lookup tables the wiki lists in the routine range.
- **Padding**: a run of `nop` with no `jr $ra`.
- **Sony library/middleware**: per AGENTS.md, these are not reconstructed.

## Narrowing, ordering, and library expansions

- **A lone `move rX,rY` before a compare** is the tell for a *second, narrower*
  local. Changing a clamp temp from `s32` to `u8` was exactly the difference
  between 188 and 192 bytes in `battle_handle_steal_exp`.

- **GCC 2.6.3 reorders neither loads nor stores here.** A `lhu` that sits in the
  wrong place is controlled purely by where the load appears in source order —
  move the read, do not try to trick the scheduler.

- **An `lwl`/`lwr` pair alongside an aligned copy path** is GCC's `movstrsi`
  expansion of `memcpy`, not hand-written assembly. Write the `memcpy` and it
  reproduces exactly (`copy_xy_coords_and_map_tile_data` is plain
  `memcpy(dst, src, 0x1000)`).

## Shell gotchas in worker loops

- `set -- $r` does not word-split in zsh; use `${=r}`.
- Do not pipe `make` into `head` or `tail -1` inside a loop — the SIGPIPE
  surfaces as a spurious `Error 1` that looks like a build failure.
- Always redirect `</dev/null` into `make`; otherwise a prompt can hang a worker
  until the stream watchdog kills it.

## Constant folding and address arithmetic

GCC 2.6.3 aggressively folds constants into load/store displacements. When the
target keeps the constant as a separate `addiu`, split the address into its own
statement so there is nothing left to fold:

- `p = arr[id] + k*3 + 0x7A; p[i>>3] |= ...` reproduces a target that adds the
  constant *before* the variable index. Written as one subscript, `0x7A` folds
  into the `lbu` displacement instead.
- `idx = n - 0x90; arr[idx * 2]` keeps the target's `addiu`/`sll` pair;
  `arr[(n - 0x90) * 2]` distributes the constant into the `%lo` displacement.
- GCC hoists pure constants (`li 0x12`) out of conditional blocks, but does not
  hoist `reg + imm`. If the target materializes a constant in a branch, it was
  probably `reg + imm` in the source.

## Signedness and width of temporaries

- `u32` vs `s32` on a bitfield temp is exactly the difference between `srl` and
  `sra`.
- A plain `s16` local produces the `(x<<16)>>15` doubling idiom and the
  `sll`/`sra` compare shape; do not reach for explicit casts first.
- At `-O0`, `x * 0x100` and `x << 8` are **not** interchangeable — the shift form
  emits an extra `move`. (At `-O2` they converge.)

## Branch and loop shapes

- `dst = p + 0xF; if (cond) dst = p + 0x12;` (assign-then-override) reproduces
  the "else arm lives in the branch delay slot" pattern. A symmetric `if/else`
  costs an extra `j`.
- To make GCC hoist a loop-invariant into the preheader *after* another hoisted
  value, the expression must be unconditional in the loop body but textually
  after the first use of the other value — e.g. `cmp = a < b;` then
  `w = x + 0x40;` then `if (cmp)`.

## Jump tables need an explicit .rodata placement

A `switch` dense enough for GCC to emit a jump table puts the table in
`.rodata`, and the table must land at the target's address or the `lui`/`addiu`
that loads its base is wrong.

Two places must agree:

1. The wip `.ld` needs the placement, e.g.
   `.rodata 0x80067578 : SUBALIGN(4) { *(.rodata) *(.rodata.*) }`.
2. The promoted record in `modules.yaml` needs a matching `verified_ranges`
   entry. `cmd/tools/linker.go` only emits a `.rodata` line in the generated
   linker script when that entry exists, so a promotion that omits it links the
   table wherever the linker likes -- and `make wip ACTION=match` still passes,
   because the wip build used your `.ld`. The breakage only appears at the next
   full `make build`.

`scripts/promote_wip.py` now refuses to promote when the `.ld` pins `.rodata`
but `--rodata-bytes` was not supplied, so pass the table size:

```sh
python3 scripts/promote_wip.py ... --rodata-bytes 20
```

The size is (number of table entries) * 4. Confirm it by reading the target: the
entries are addresses inside the function, and the first value that is not one
marks the end of the table.

## Wiki address ranges are not always exact

The routine listings are a decades-old community artifact and the end address is
occasionally short. `world_get_known_skillsets` is listed as ending at
`0x80122880`, but the real function is 244 bytes and ends at `0x80122884`.

If a draft is otherwise correct but four bytes short, suspect the range before
suspecting the source. Confirm against the disassembly -- the function ends at
its `jr $ra` plus the delay slot -- and promote with the corrected `--end`.

## Frame layout and spill slots

- `struct { s32 *p; s32 unused[3]; } local;` places the pointer at `sp+0x10`
  with padding *above* it. A bare `s32 unused[N]` always lands below the reload
  spill slot, so it cannot reproduce that layout — use the struct when the
  target reloads from a slot your build spills below.
- A dummy `s32 pad;` declared before the real locals shifts frame slot
  assignment, useful for landing a local at a specific `$fp`/`$sp` offset.
- `__asm__("" : : "r"(param));` placed after the first statement forces the
  parameter's move into a callee-saved register to be emitted at that point,
  which can fill a load-delay slot. This is a legitimate small hint, not an
  asm reimplementation — it emits no instructions of its own.

## When to stop hand-editing and reach for the permuter

If a draft is size-exact (or within a few bytes) and the *only* remaining
difference is which registers were chosen or where two independent instructions
sit relative to each other, hand-editing has essentially run out. Workers on this
project have repeatedly burned 4-6 variants on that class of diff without moving
the allocator. Park it in `wip/` with a precise note about the residual diff and
run `make wip ACTION=prepare` / `ACTION=permute` instead.

Permuter output must be cleaned up before it enters `src/` — restore real
variable names and drop the generated scaffolding, then re-run
`make wip ACTION=match` to confirm the cleaned version is still byte-exact.

## Cross-jumping: write the duplication you want to see

This is the single highest-value technique found so far.

When the target ends in one call reached from many paths, write each path as its
own complete `f(args); return;`. GCC cross-jumps the identical tails on its own,
leaving exactly the differing argument setup plus the `j`/branch. Writing it the
"clean" way instead — `a = X; b = Y;` and a single call at the end — produces
correct semantics but the wrong block ordering, and no amount of `goto` juggling
recovers it. This flipped `battle_setup_unit_moving` after twelve failed
structural variants, and `set_item_throw_stone_ability_display_stuff`.

The converse is a diagnostic: if GCC emits one shared block where the target has
two, the target's source had two independent `if` statements each with a full
early return, not one `||` condition.

`if (a == 0 || a == 0x200) ...`      -> one shared block
`if (a == 0) { ...; return; }`
`if (a == 0x200) { ...; return; }`   -> two blocks, as the target has

## Operand order in `addu` (corrected)

An earlier version of this file claimed `unit[0xBE + j]` and
`*(unit + j + 0xBE)` select the two `addu` operand orders. That is wrong — on
the raw *parameter*, `p[CONST + i]`, `p[i + CONST]`, `*(p + i + CONST)` and
`i[p + CONST]` all produce the reversed `addu rd,idx,ptr`.

What actually works is a **local copy of the pointer**:

```c
u8 *q = p;
... *(q + i + CONST) ...   /* addu rd,ptr,idx */
```

## Comparison signedness

`sltiu` vs `slti` on a byte value is controlled by the declared type of the
temporary, not by casts:

```c
u8  v = x + 2; if (v < 2)            /* sltiu */
s32 v = ...;   if ((v & 0xFF) < 2)   /* slti  -- GCC's range info narrows it */
```

## Assign-then-override polarity

`x = A; if (cond) x = B;` puts `A` in the branch delay slot. To get the target's
`bnez -> A / j -> B` shape instead, write:

```c
if (cond) { x = A; goto L; }
x = B;
goto L;
```

GCC inverts the condition and swaps the arms exactly once.

## Working from m2c output

- m2c's `temp_v1_NNN` / `temp_a0_NNN` local names encode the register the target
  used. Pinning them with `register ... __asm__("$3")` is a fast way to converge
  on the target's allocation. But pin only non-overlapping live ranges: pins on
  overlapping ranges introduce `move`s and make the diff worse.
- `__asm__ volatile("")` is an effective scheduling fence when the target leaves
  a load-delay `nop` that your build fills. Like the `"r"(param)` hint, it emits
  no instructions itself.

## GCC 2.6.3 merges identical `||` arms

Syntactically identical arms of an `||` chain get cross-jumped into one block.
When the target shows the range checks duplicated, write them as separate `if`
statements:

```c
if (v >  0x7800) return;      /* three separate ifs, as the target has */
if (v >  0x6800) return;
if (v < -0x6800) return;
```

## Sanity-check the wiki's function sizes

Two independent cases this session where the wiki range was wrong:
`world_get_known_skillsets` is 4 bytes longer than listed, and
`HELPMENU.OUT General Handler` is 3460 bytes, not the 3968 its range implies.
Derive the size from the disassembly (prologue to `jr $ra` + delay slot) before
concluding a draft is the wrong size.

## Loop induction variables

Usually you fight GCC's strength reduction by giving it a walking pointer. The
reverse also happens: *removing* an explicit walking pointer and indexing the
array arithmetically (`base[i*0x20 + 0x71]`) can stop strength reduction from
eliminating the `i` induction variable the target keeps. If the target has an
obvious counter your build optimized away, try indexing instead of walking.

## Boolean merges, precisely

Which `goto` you write decides which way the merge breaks:

- `goto ret1;` past a `return 0` fixes the `xori rd,rd,1` shape when the compare
  is an `slt`.
- `goto ret0;` past a `return 1` fixes the `sltiu rd,rd,1` shape.

Both work by giving the two constant returns separate blocks; picking the wrong
one leaves the merge in place.

## Duplication may need to go one level deeper

The cross-jump trick sometimes requires the call duplicated inside *each sub-arm
of a nested `if` within a switch case*, not merely once per case. In
`battle_confirm_action` that is what put the common `li a0,4` into the `beqz`
delay slot.

## Switch case bodies are emitted in source order

For a `switch` with empty cases, the case bodies must appear in the target's
order in the source (e.g. `0x800`, `0`, `0x400`, `0xC00`), not in numeric order.


## One local per basic block controls register assignment

Reusing a single local (`u8 *action;`) across several mutually exclusive blocks
lets GCC 2.6.3 coalesce them into one pseudo, and the allocator then picks a
register for the *union* of the live ranges. When the target uses a different
register in each block, give each block its own local:

```c
if (...) { a = g_ptr; ... }        /* target: $a0 */
else     { b = g_ptr; ... }        /* target: $v1 */
```

This was the whole difference in `battle_hp_absorbtion` (three blocks, three
locals) and in `elemental_damage_modification_2` (one `action` local per `if`).
It is the cheapest thing to try when the diff is only `r` (register) marks and
the instruction sequence is otherwise identical.

## Pinning one register is often enough to unstick the rest

`register T v __asm__("$N");` on a *single* value, combined with per-block
locals, converged three functions this session where nothing structural moved
the allocator:

- `elemental_damage_modification_2`: the parameter copy `move $a1,$a0` that
  fills the load-delay slot only appears if the element mask is pinned to `$5`.
  Passing the parameter on to the callee does *not* produce the copy.
- `some_kind_of_entd_unit_manipulation`: two saved bytes wanted `$s3`/`$s4` in
  the opposite order from what GCC picked, and neither declaration order nor
  statement order changed it. Pinning both (`"$19"`, `"$20"`) matched.
- `event_instructions_a0_a5`: see below.

Pin different registers to values with overlapping live ranges; pinning two
overlapping ranges to the *same* class is what introduces spurious `move`s.

## Unfilled branch delay slots: look at the first insn of the fall-through

GCC copies the branch target's first instruction into the delay slot (and
retargets past it) only when that instruction's output is dead on the
fall-through path -- and its check is shallow: the fall-through's *first*
instruction has to be the one that kills the register.

In `event_instructions_a0_a5` the target fills five `bne` delay slots with the
next `li v0,0xNN`, because each block begins `lui v0,0x8016`. Our build put the
pointer in `$a0` (the now-dead opcode parameter), so `v0` was killed three
instructions later and GCC gave up and emitted `nop`. Pinning the pointer to
`$2` filled all five slots and took the function from 280 to 264 bytes.

## `__asm__ volatile("")` as a store/setup ordering fence (confirmed again)

In `world_bin_prepare_job_name_on_job_wheel` GCC sank a global store four slots
past the outgoing-argument setup. A bare `__asm__ volatile("")` immediately
after the store pinned it. It emits nothing and costs no bytes. Use it
sparingly -- it also blocks *wanted* hoists, so place it at exactly one point
and re-check the rest of the diff.

## Trailing global stores get reordered; source order is not output order

GCC 2.6.3 *does* reorder stores to distinct global scalars (it schedules by
operand readiness). A tail of

```c
D_801C8450 = <long dependency chain>;
D_801C8452 = 0xD7;
D_801C8454 = width;
D_801C8456 = 0xE;
```

comes out as `8450, 8454, 8452, 8456` with the `li 0xD7` hoisted into the gap
after the first store. Write the stores in *address order* and let the
scheduler produce the target's interleave, rather than transcribing the
target's emitted order back into the source.

## Signed pointer comparison

`slt` (not `sltu`) on a pointer bound means the source compared the pointers as
signed integers. `while ((s32)p < (s32)end)` reproduces it; a plain `p < end`
gives `sltu`. (`battle_learn_from_crystal`.)

## Loop preheader ordering

The order of the preheader's setup instructions follows source order exactly.
If the target does `move t1,zero / la t0,tbl / move a0,base` but your build
emits the table address first, move the counter's `i = 0;` above the other two
initialisers and write the loop as an explicit `do { } while`.

## Deriving a global's address from `lui`/`%lo`

The `%lo` half is **signed**. Adding it to the `lui` immediate as if it were
positive gives an address that is wrong by 0x10000:

    lui  $v0, 0x8019
    addiu $v0, $v0, -0x2e60     ->  0x8018d1a0   (NOT 0x801951a0)

A draft built on the wrong address diffs only in the `lui`, which reads like a
relocation or scheduling problem and sends you looking in the wrong place. When
a diff is confined to a single `lui`, re-derive the address with the sign before
touching anything else.

## Increment of a global that the target reloads

When the target loads a global twice and adds one, `G = value + 1` folds to a
materialized constant (`li v0,2`). Reproducing the reload needs the comparison
and the increment written against the global itself:

```c
if (G == 1) G = G + 1;      /* second load is CSE'd, not const-propagated */
```

Pair it with a dummy `s32 unused;` when the target's frame is larger than your
locals justify.

## Padding a frame: `char` arrays survive DCE

The usual `s32 unused[N]` trick for forcing a larger stack frame does not always
hold. For an 8-byte no-save frame, `char unused[8];` worked where **both**
`s32 unused[2];` and `volatile s32 unused;` failed -- GCC 2.6.3 eliminates the
`s32` array but keeps the `char` one.

If `s32 unused[N]` is not producing the frame you expect, try `char unused[N]`
before concluding the frame size comes from something else.

## Ask the compiler why it hoisted: `cc1 -dl` inside the container

When a loop-invariant address lands in the preheader but the target keeps it
in the loop (or vice versa), do not guess. The wip build leaves the
preprocessed file at `build/wip/<name>/gcc-2.6.3_O2_aspsx-2.34.i`; run
`cc1` on it by hand with a dump flag:

```sh
docker run --rm --user "$(id -u):$(id -g)" --env HOME=/tmp \
  --volume "$PWD:/work" --workdir /work/build/wip/<name> fft-decomp-dev \
  qemu-i386 /opt/old-gcc/2.6.3-psx/cc1 x.i -o x.s -G0 -w -funsigned-char \
  -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm \
  -msoft-float -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff -O2 -dl
```

`x.i.loop` then says, per insn, `move-insn savings N not desirable` or
`moved to NNN`, lists every biv/giv with `replaceable` or not, and shows
which giv became the base of a combined address register. `-df` adds the
`Register N used M times across L insns` lines that drive allocation
priority, `-dj`/`-ds` give the pre-loop RTL. Copy the flags exactly from
`cmd/tools/main.go`; `-gcoff` matters because line notes count in luids.

## GCC 2.6.3 hoists `la sym / addu` unless the index is set in the loop

An address `sym + idx` inside an inner loop is hoisted when `idx` is a
register that no insn in the loop writes, even when the loop has a call. Two
things follow:

- The retail code frequently keeps `lui/addiu/addu` inside the loop. A
  zero-byte `__asm__("" : "=r"(idx) : "0"(idx));` placed inside the loop
  counts as a set of `idx`, which makes the address non-invariant and stops
  the hoist. That is what most of the existing `"=r"(x) : "0"(x)` hints in
  `src/event` are doing; they are not fences.
- Indexing the table by the outer counter (`tbl[i]`, so the `mult` is in
  the loop) also keeps the `addu` in place, but the strength-reduced giv is
  then *not replaceable* ("Previous line always fails if INSN was moved by
  loop opt") and GCC emits a copy of it in the inner preheader. If the target
  has no such copy, the source had an explicit `idx += 12` counter.

## Six-argument call with a store in its delay slot is plain C

`sw $2,0x10($29)` / `sw $2,0x14($29)` followed by `jal` with a `sh` in the
delay slot is just `f(a, b, c, d, e, g)` preceded by the store statement.
GCC 2.6.3 fills the `jal` delay slot with the last independent store on its
own. Do not keep such a block as asm because of the delay slot.

## Pinning frees a register; GCC then hoists a constant into it

In a loop that uses all nine callee-saved registers, pinning one variable
with `register ... __asm__("$N")` can make the allocator give a *different*
callee-saved register to a hoisted constant (`li s0,1`), which changes the
instruction stream (`li t0,1` disappears from the loop). If the target keeps
small constants in `t0`/`t1` inside the loop, all s-registers are occupied
and pins will not converge — fix the priority inputs (refs and live length)
instead.

## Memory-resident locals: a small struct, not `volatile`

A local that the target keeps on the stack and reloads (`lw t0,0x18(sp)`
inside the loop) is reproduced by putting it in a small local `struct`;
GCC 2.6.3 never promotes struct members to registers, and the struct also
fixes the frame slot layout. `volatile` reproduces the loads but blocks the
scheduler from interleaving them with the argument setup.

## Do not re-declare library prototypes

`LoadImage`, `DrawSync` and friends are already declared in `include/psx/gpu.h`.
Re-declaring one in a reconstruction is a hard compile error, not a warning.
Include the header and use the existing declaration.


## Struct pointers reproduce a biased induction pointer

When the target walks fixed-size packets with one pointer biased to the *last*
field written (`sh v0,-6(a0) ... sh v0,0(a0)` from `menu + 0x26`, or
`sb v0,-2(a1) ... sb v0,0(a1)` from `menu + 0x1e`), a raw `u8 *p = menu + 0x26`
with negative offsets makes GCC split the walk into two induction pointers (and
previous workers pinned `p` to get one). Declaring the packet layout and
walking a typed pointer reproduces the bias with no pin:

```c
typedef struct { u32 tag; u8 r0, g0, b0, code; s16 x0, y0, x1, y1; } MenuLineF2;
MenuLineF2 *line = (MenuLineF2 *)(menu + 0x18);
do { line->x0 = ...; line->y0 = ...; line->x1 = ...; line->y1 = ...; line++; } while (...);
```

(`initialize_numeric_display_frame_primitives`,
`initialize_menu_primitive_colors_palette_bank_0/1`.)

## Biased induction pointer into a struct array: pointer arithmetic, not subscript

When the packet array sits *after* a header (`struct { u8 header[0x10];
SPRT sprites[25]; }`) and the target's strength-reduced pointers are biased
from the block base (`addiu v0,s3,0xdc / sh v1,0x32(v0)`, stepping by 0x14),
the two ways of writing the same element access compile differently:

```c
primitives->sprites[i + 1].clut = clut;          /* WRONG: (i+1)*0x14 stays its own
                                                    counter, header folds to a 0x1e
                                                    displacement */
(primitives->sprites + i + 1)->clut = clut;      /* RIGHT: constant part folds at tree
                                                    level to base + i*0x14 + 0x32, then
                                                    strength-reduces to the biased pointer */
```

The exception is a call *argument*: `SetShadeTex(&primitives->sprites[i + 20], 0)`
(subscript) yields the target's separate integer giv (`li s2,0x1a0 / addu a0,s3,s2`),
where the pointer form adds an extra `addiu`. Mixing the two -- subscript for the
argument, pointer arithmetic for the field stores in the same loop body -- is what
matched. This replaced three raw `u8 *` walkers plus two `register __asm__` pins in
each of `attack_configure_status_panel_primitive_colors`,
`bunit_/debugchr_configure_status_panel_primitive_colors` and
`require_configure_postbattle_status_panel_primitive_colors` (no pins, no raw
walkers, byte-exact).

## Record walks that start *below* the array: index from the base

The sprite display initialisers write the 7-byte part records via a pointer
that starts at the slot base and uses offsets `0xe..0x14`, then steps by 7.
`SpritePartDisplayData *part = (SpritePartDisplayData *)display; part[2].u = ..;
part++` reproduces that exactly (`part[2]` folds to the 0xe displacement).
Starting at `display->parts` instead adds an `addiu` and changes the walk.

Two more things that loop needs: `volatile` on the walking pointer, or GCC
strength-reduces it to a pointer biased by +0x14 with negative displacements;
and a `__asm__ volatile("" ::: "memory")` before `count++`, or the increment is
hoisted above the stores. (`battle_initialize_{status_bubble,item,weapon}_sprite_display`,
`battle_set_sprite_part_flag_bit_0`.)

## Count-up loops that the target runs backwards

`for (i = 15; i >= 0; i--) *p++ = 0xfe;` emits `li v0,0xf` before `li v1,0xfe`;
the target had the constant first. `for (i = 0; i < 16; i++) *p++ = 0xfe;`
matched: GCC reverses the loop itself and orders the preheader the target's way
(`battle_fill_text_field_with_terminators`). Try the count-up form before
fighting preheader order by hand.

## `addu rd,idx,base ; addu rd,rd,ptr` — sum the indices first

`grid[i + base] = 0` and `(i + base)[grid]` both emit `addu rd,ptr,sum`. To get
the target's `addu v0,v1,a2 ; addu v0,v0,t0` write the pointer add last and as
an integer: `*(u8 *)((i + base) + (u32)grid) = 0;` (`free_battle_memory`, which
replaced a 12-word `.word` block).

## Keep a parameter out of a callee-saved register

If the target keeps a pointer parameter in `$a3` and only saves a *copy* in
`$s1` inside the interesting branch, copy it to a local at the top of that
branch and never touch the parameter again (including in later calls and the
epilogue code). Using the parameter after the calls forces GCC to home it in
`$s3` for the whole function (+1 save, +8 bytes of frame).
(`process_map_gns_record`, whose hand-scheduled `.word 0x0c04ed64` block is now
three `battle_get_script_variable` calls; the chained masks match with one
local per step, as in `load_map_mesh_variant`.)

## Per-block pointer locals materialise the address per block

`u8 *red = &g_color[0]; ... { u8 *green = &g_color[1]; ... }` gives a fresh
`lui/addiu` in each block, where a single `u8 *color = g_color` with `color[1]`
folds into one base and an `addiu`. (`battle_adjust_background_color`.)

## Hand-expanded `addPrim` tails: use `P_TAG` `setaddr`/`getaddr` (confirmed x10)

Event-overlay primitive enqueuers end with the libgpu `addPrim` link written
out by hand -- `command_mask = 0xff000000; address_mask = 0xffffff;
poly->tag = (poly->tag & command_mask) | (ot[i] & address_mask); ...` -- and
then need `register ... __asm__("$5"/"$6")` pins on the masks to match. The
sibling `bunit_out_001cd344_001cd440.c` form matches with no pins in every
card/equip/bunit twin tried (10 files, tile / POLY_FT4 / DR_MODE / DR_MOVE):

```c
typedef struct { u32 addr : 24; u32 len : 8; } P_TAG;
#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p) ((u32)((P_TAG*)(p))->addr)
typedef struct { u32* ot; u8 pad[0x38]; Tile* tiles; } GfxCtx;  /* per overlay */
...
{
    GfxCtx* context = g_graphics_context;
    setaddr(prim, getaddr(&context->ot[otag_index]));
    setaddr(&context->ot[otag_index], prim);
}
```

Keep the `context` local inside its own block and keep the two statements
separate (the store between them is what makes GCC reload `context->ot`).
The exception is a loop that reuses the masks many times
(`card_build_scaled_sprite_primitive_chain`): there the target hoists both
masks into `$s6`/`$s7`, and the mask-local form with pins is the right one.

## `(u8)` in an initializer places the `andi` early and defeats CSE of a second `& 0xff`

When the target computes `unit_id & 0xff` twice (once for an index, once for a
call argument) and emits the first `andi` *before* the table `la`, write the
index as `u32 idx = (u8)unit_id;` and the later argument as `unit_id & 0xff`.
GCC emits the zero-extension at the initializer and does not CSE it with the
explicit `and` (`bunit_calculate_unit_jobs`; `u8 idx = unit_id;` defers the
`andi` to its use, after the `la`, and `unit_id & 0xff` twice is CSE'd).

## `move rX,rY` copies at join labels are plain assignments

A target that re-copies a live variable into a scratch register right before
each test at a join point (`move v0,s2; bnez v0`), with the copy also appearing
in the predecessors' branch delay slots, is just `state_value = reverse;`
written at the join label. CSE cannot propagate the copy across a
multi-predecessor join, and the delay-slot filler hoists it into the incoming
branches. No identity `__asm__` is needed (`card_update_and_draw_animated_cursor`,
six asm sites removed). In the same function `lbu / sll 24 / sra 24` was the
`(s8)` cast applied *after* the if/else that loads the byte in each arm -- two
reaching defs stop combine from folding it into `lb`.

## Early-return getters put the constant in `$v0`

For `if (v) return v; return C;` shaped getters where the target has
`beqz v1 / lui v0,C` with `move v0,v1` on the fall-through, write
`if (value == 0) return C; return value;`. The assign-then-override form
(`r = C; if (v) r = v; return r;`) allocates the result to `$v1` and adds a
trailing `move` (`equip_get_menu_display_value_1/2`, `equip_get_speed_multiplier`).

## Narrower locals that keep a copy alive (three more confirmations)

- `move v1,v0 / slti v0,v0,4` before `addiu v0,v1,1`: the copy is an `s16`
  local (`s16 previous = current;`) -- `s8` and `u8` do *not* reproduce it
  (`equip_parse_advance_transition_frame`).
- `sltiu v0,v0,1 / move a0,v0`: declare the destination `u8 changed;` and the
  source `s32`; GCC keeps the two registers instead of coalescing
  (`equip_out_entrypoint`).
- `result = (ability >> 14) == 0` where the target does `srl / sltiu` in a
  fresh register: `u16 ability = *entry;` (a `u32` local coalesces and needs
  pins) (`bunit_/jobstts_is_non_action_ability_learned`).

## Nested `do { } while` vs. goto-labels changes allocation

The same 5x5 scan written with labels/`goto` and with two nested `do/while`
loops differs only in which of `$a2`/`$a3` holds the row counter. For
`attack_remove_roster_unit_from_deployment_tiles` the nested form matched with
no pin at all; for the two siblings that return a value the swap stays and one
pin is still needed. Try the loop form before pinning.

## Infinite loops keep an unreachable epilogue

`for (;;) { f(); }` compiles to `jal f / j loop` followed by the normal
`lw ra / addiu sp / jr ra` epilogue: GCC 2.6.3 emits the epilogue textually
whether or not it is reachable. A `__asm__("j <jal address>")` after the call
is never needed (`world_yield_forever`, `world_idle_thread_wait_forever[_b]`,
`world_idle_thread_yield_forever`).

## Effect state handlers: `switch` over phases 0-3 with an `s32` return type

The E###.BIN phase handlers test `== 1`, `< 2`, `== 2`, `== 3` with `nop`s in
the branch delay slots. Two things reproduce that from plain C with no
`__asm__ volatile("" ::: "$2")` clobbers:

- `switch (state->phase) { case 0: break; case 1: ... case 2: ... case 3: ... }`
  -- the (empty) `case 0` roots GCC's decision tree at 1; without it the tree
  is balanced at 2 (`== 2` first, then `< 3`).
- declare the handler `s32` and fall off the end -- `$v0` is then live at the
  exit label, so `li v0,2` / `li v0,3` cannot be hoisted into the delay slots
  of branches that go there. A `void` handler fills them.

(14 handlers in e450/e453/e454/e455/e456/e458/e480, and the dispatch of
`effect_e464_altimas_transformation_update_particle_state`.)

## A callee prototype returning `s32` keeps an `s16` copy in its own register

In `world_unit_animation_rotate` the target copies the call result to `$a0`,
copies that to `$s1` in a delay slot and sign-extends `$a0` per arm. With
`extern s16 world_get_misc_id()` and two `s16` locals GCC merges the copy and
extends from `$s1`; pinning was the previous fix. Declaring the callee
`extern s32 world_get_misc_id(s16)` (which is how the rest of `src/world`
declares it) and keeping `s32 call_misc_id; s16 misc_id;` matched with no pin.

## `addu rd,ptr,idx` for a global's own address: index the symbol directly

`state[g_x + 7]` with `int *state = &g_x` gives `addu v0,v0,s0` (index
first) however the sum is written -- casts, `char *`, separate offset local.
`(&g_x)[g_x + 7]` gives the target's `addu v0,s0,v0` while a `state[g_x] = ..`
store in the same function stays index-first (`poll_scenario_smd_file_load`,
replacing an `__asm__("addu ...")`).

## `s32` temps for table bytes avoid a stray zero-extend `move`

`u8 id = table[i]; ... while (*p == id)` emits `move a0,a1` before the loop
(the `u8` is re-extended for the int compare). `s32 id = table[i]` compares
directly (`game_free`, which previously pinned `id` to `$5`).

## WLDCORE: a `nop` between `lw` and a `sw sym` macro is ASPSX 2.21

`x = g_a; g_b = x;` assembled with 2.34 gives `lw v0 / lui at / sw v0,%lo(at)`;
2.21 inserts the load-delay `nop` before the macro. Do not add
`__asm__ volatile("nop")` -- build with `PROFILE=gcc-2.6.3_O2_aspsx-2.21` and
record `canonical_profile` (`world_process_frame_gate`). Same rule as the
indexed-global `$at` form above.

## Hand-assembled WORLD helpers (do not try to de-asm)

`world_get_{first,second,third}_thread_parameter`,
`world_check_{previous_thread_running_status,thread_running_status_by_id}`,
`world_get_inner_text`, `copy_bytes` use `$at` as a load base, `$t0-$t2`
scratch, trapping `add`/`addi`, and unfilled delay slots. GCC never emits any
of those; the `$1` pins and file-scope `.set noat` are the minimal form.

## Struct-member loads are hoisted across scalar global stores

GCC 2.6.3's scheduler treats a load through a struct member (`unit->position.raw`,
MEM_IN_STRUCT_P) as never aliasing a store to a scalar global, so it hoists
the load above the store. The retail code read through a plain `u8 *`, so the
load stayed below the `sh`. When typing a file with `BattleStats *` moves a
load upward in the diff, read that one field through a cast pointer:

```c
D_801938A2 = x - unit->x;                                   /* sh */
facing = (*(u16 *)&unit->position >> 8) & 0xF;              /* lhu stays after the sh */
```

`unit->position.raw` in the same spot hoists the `lhu` above the store
(`current_action_attacker_data_setting`).

## Bitfield reads are shorter than the target's shift/mask

`unit->position.bits.facing` compiles to a narrower extract than the
`lhu / srl 8 / andi 0xf` the target emits. When the target has the explicit
shift and mask, write `(raw >> 8) & 0xF` on the halfword; the `.bits.y`
low-byte read does reproduce a plain `lbu` (`set_target_coordinates_for_ability`).

## Typing `g_ai_data_base`: direct vs pointer access is per site, and walks start at the base

`BattleAiData` (include/fft/battle.h) replaces the `base[0xNNN]` indexing of
the AI block.  Two things carried over from the raw form:

- The `lui $at` / `%lo` sites are `g_ai_data_base.field`; the `$s0`-relative
  sites are `ai->field` through `BattleAiData *ai = &g_ai_data_base;`.  The
  same function mixes both (`check_if_map_allows_use_and_find_highest_target`,
  `chose_move_from_move_list`), exactly as it did with the raw array.
- A per-unit loop whose pointer the target starts at the block base
  (`move s2,s4`) and dereferences with the record's absolute displacement
  (`lbu 0x1834(s2)`) is *not* `BattleAiUnitDecision *d = ai->unit_decisions;
  d++` -- that adds an `addiu 0x182c`.  Keep a `u8 *walk = (u8 *)ai;
  walk += sizeof(BattleAiUnitDecision);` and read
  `((BattleAiUnitDecision *)(walk + 0x182c))->enemy_flag`
  (`set_unit_untargetable_based_on_19f0d8_routine`).

`ai->ranked_actions[i].base_hit_percent` with a struct stride of 0x20 keeps
the same induction variable as `base[i * 0x20 + 0x71]` (`randomly_transfer_data`),
and `&g_ai_data_base.selected_action` assembles to the same `lui`/`addiu` as a
separate `D_801A0BC0` symbol (`battle_func_8019ae30`).

## Check the target's load width before trusting the header's field type

`BattleStats.action_target_x/_y` are `s16`, but
`current_action_attacker_data_setting` loads them with `lbu`. Typing the
access as the field gives `lh` and a 12-byte shorter function. Keep the
byte access through the field's address, `*(u8 *)&unit->action_target_x`,
with a comment; do not widen the header field to fit one reader.

## Confirmed on OPEN.BIN (24 functions moved to the 2.21 profile)

- GCC 2.6.3 computes `(c ± 1) * stride` before folding, so index the symbol at
  the biased base rather than adjusting the index.
- A `volatile u8 *` walking pointer stops the biased-induction split that a
  plain pointer suffers.
- A struct-member load hoists above scalar-global stores (the same rule as
  `called_by_nullify_action`); use it deliberately to reproduce a reload.
- The homing sequence `sw a3 / lw a0, lw a2 / sw, sw` is an 8-byte struct
  parameter passed by value.
- `(x + (x >> 31)) >> 1` on a **u32** is not signed `/ 2` -- the final shift is
  `srl`. Write it as the expression, not the division.
- maspsx recognises `.set noreorder` only when it is tab-indented.

