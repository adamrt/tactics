# Permuter queue

Drafts in `wip/` that are structurally correct and byte-exact except for
register allocation or instruction scheduling. Each already had 3-12 hand
variants tried without moving the allocator, so they are permuter work, not
hand-editing work (see docs/matching-cookbook.md, "When to stop hand-editing").

    make wip ACTION=prepare MODULE=<module> SYMBOL=<symbol>
    make wip ACTION=permute MODULE=<module> SYMBOL=<symbol>

Permuter output must be cleaned up before it enters `src/`, then re-verified
with `make wip ACTION=match`.

| module | symbol | address | residual difference |
| --- | --- | --- | --- |
| battle | `call_ai_ability_processing` | 0x8019dcbc | 1 register off: $3 vs $4 for the base[0xCBA] reload after the call; everything else byte-identical |
| battle | `effect_palette_setup` | - | one register apart: size lands in $a0 instead of $v1 (addu v1,a0,v1 vs addu a0,a0,v1) |
| battle | `set_unit_untargetable_based_on_19f0d8_routine` | 0x8019f01c | 188/188 bytes, structurally identical; only s1<->s2 allocation for the p/unit pointers |
| battle | `event_instruction_add_ghost_unit` | - | exactly 228 bytes, IDENTICAL instruction stream; only callee-saved assignment differs |
| world | `world_get_known_skillsets` | 0x80122488 | size-exact 244, 4 instructions shuffled; note real end is 0x80122884 (wiki is 4 short) |
| battle | `unitanimrotate_event_instruction` | 0x80147fac | instruction-for-instruction correct; GCC uses 3 callee-saved (frame 0x20) vs target 4 (frame 0x28) |
| event-bunit | `bunit_out_001cb058_001cb130` | - | size-exact 220B; six u16 temps get registers in exactly reverse order |
| battle | `prep_for_special_status_flag_enabling` | 0x80180fe4 | 188/188 bytes, 4-instruction scheduling window at +0x60 |
| battle | `unlockdate_event_instruction` | 0x8013dae4 | 184/184 bytes, single divergence at +0x68 (loop-invariant hoist) |
| event-option | `option_render_menu_entries` | 0x801bf000 | 484 vs 480; byte-exact 0x00-0x68 and 0x84-0x1dc; frame spill/reload shape |
| event-helpmenu | `helpmenu_require_handler` | 0x801dfe10 | ~40% byte-exact; residual is reg-alloc/scheduling in two POLY_FT4 branches (GCC hoists coord addu/addiu above the sb stores). ~30 hand iterations already spent. |
| battle | `compare_set_highest_unit_target_priority` | - | 248/248 bytes; two swapped preheader instrs + s1<->s3 swap (dst-offset vs i). Pure register allocation. |
| battle | `non_specific_ai_autobattle` | - | 256 vs 260 bytes; single instruction: target duplicates `move v0,zero` into a beq delay slot instead of branching to the shared block |
| battle | `unit_graphic_information_loading` | - | 268 vs 264; our build strength-reduces the loop address and hoists invariant flags&0x61; target recomputes sll/addiu/addu each iteration with 5 saved regs |
| wldcore | `wldcore_test_bit` | 0x80092148 | 52 vs 56 bytes; identical instruction stream except the target's leading `move a2,a0` — it allocates `index & 31` to $a0 and spills the `bits` pointer to $a2. Pure register allocation. |
| wldcore | `wldcore_store_800d07d8_entry` | 0x8008fc88 | 60 vs 64 bytes; GCC hoists the second `lh` (D_800BB356) above the first `sw`, filling the load-delay slot the target leaves as `nop`. Scheduling only. |
| world | `world_func_80128c7c` | 0x80128c7c | 48/48 bytes; only the two prologue saves are swapped (target `sw ra,0x14 / sw s0,0x10`, ours `sw s0,0x10 / sw ra,0x14`). sched2 promotes `sw s0` because the anti-dependency `sw $16` -> `move $16,$7` (first jal's delay slot) makes it the longer path. Structural variants (4-arg first callee, `asm volatile("")` fence) do not move it. |
| wldcore | `wldcore_opcode_branch_if_equal` | 0x8008c240 | 140/140 bytes; sole diff is `addu v1,v0,v1` at +0x14 (target rs = D_800D4874 reg, ours = D_800D4852 reg). Commutative-operand order tied to load order by GCC. |
| wldcore | `wldcore_opcode_branch_if_not_equal` | 0x8008c2cc | 140/140 bytes; identical single `addu` operand-order diff at +0x14. |
| wldcore | `wldcore_opcode_branch_if_less` | 0x8008c358 | 144/144 bytes; identical single `addu` operand-order diff at +0x14. |
| wldcore | `wldcore_opcode_branch_if_greater` | 0x8008c3e8 | 144/144 bytes; identical single `addu` operand-order diff at +0x14. |
| battle | `get_third_thread_parameter` | 0x8014cc28 | 36 vs 52 bytes; target loads both globals through the assembler's `lui $at / addu $at,$at,$zero / lw %lo($at) / nop` indexed expansion into `$t0`/`$t1`, ours folds to `lui/lw %lo` in `$v0`/`$v1`. No C form reaches `$at`; aspsx-2.21 profile does not change it. The world twins (`world_get_first_thread_parameter`) use inline-asm register pins for the same shape. |
| world | `world_func_80114088` | 0x80114088 | 44 vs 52 bytes; `extern volatile s16 D_801CD728[16]` is required to defeat loop reversal, but GCC still replaces the address giv with a walking pointer (`addiu v1,v1,2`) where the target recomputes `sll v0,v1,1 / addu v0,v0,a1` in the body and leaves the `bnez` delay slot empty. for/do-while, sized/unsized array, arithmetic index, volatile lvalue cast, asm fences at both ends of the body and the O0 profile all fail. |
| world | `world_func_80126374` | 0x80126374 | 48 vs 52 bytes; target leaves both delay slots empty (`bnez a0 / nop / li a0,1 / jal / nop`). A `volatile s32` argument local empties the jal slot but grows the frame 0x18 -> 0x20. Same "no delay-slot filling" signature as world_func_80114088; no -O1 profile exists. |
