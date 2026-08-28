#include "psx/gpu.h"
#include "psx/types.h"

typedef struct DebugChrTexturePage {
    s16 x;
    u16 y;
} DebugChrTexturePage;

typedef struct DebugChrStatusRenderStack {
    s32 first_status;
    u8 padding[20];
    const u16* group_y_offset;
} DebugChrStatusRenderStack;

extern u8 g_debugchr_status_group_count;
extern u8 g_debugchr_status_group_ids[];
extern u8 g_debugchr_status_group_bounds[];
extern u8 g_debugchr_status_animation[];
extern const u16 g_debugchr_status_y_offsets[];
extern u16 g_debugchr_status_position_y;
extern const DebugChrTexturePage g_debugchr_status_texture;
extern const s16 g_debugchr_status_uv_rects[][6];
extern const s16 g_debugchr_status_scales[][2];
extern const s16 g_debugchr_status_offsets[][6];

extern void battle_make_default_poly_ft4(POLY_FT4* poly);
extern void debugchr_set_scaled_poly_ft4_geometry(
    u8* poly, const DebugChrTexturePage* texture, const s16* position,
    const s16* uv_rect, const s16* scale, const s16* offset);
extern void submit_primitive(void* primitive);

void debugchr_render_status_text_primitives(POLY_FT4* poly) {
    register POLY_FT4* current_poly __asm__("$19") = poly;
    register s32 group_index __asm__("$23") = 0;
    register u8* animation __asm__("$17");
    s32 offset_index;
    register u16* position_y __asm__("$22");
    register s32 status_count __asm__("$21");
    register s32 status_index __asm__("$18");
    register u8* poly_tail __asm__("$16");
    register const u16* y_offset __asm__("$20");
    /* Reserve the retail six-argument call area hidden by the scheduled asm. */
    volatile u32 call_argument_padding[2];
    volatile DebugChrStatusRenderStack stack;
    register s32 start_status __asm__("$2");
    register s32 last_status __asm__("$3");
    register s32 status_id __asm__("$6");
    register s32 active_frame __asm__("$3");
    register s32 updated_frame __asm__("$2");
    register s32 one __asm__("$8");
    register u16 x0 __asm__("$4");
    register u16 x1 __asm__("$5");
    register u16 x2 __asm__("$2");
    register u16 x3 __asm__("$3");
    u8 group_id;
    register s32 frame __asm__("$3");
    register s32 palette_frame __asm__("$2");
    register u32 temp_v1 __asm__("$3");
    register u32 temp_a3 __asm__("$7");
    register u8* geometry_poly __asm__("$4");
    register const DebugChrTexturePage* texture __asm__("$5");
    register const s16* scale __asm__("$2");
    s32 initial_group_count = g_debugchr_status_group_count;
    s32 continue_groups;

    if (initial_group_count > 0) {
        position_y = &g_debugchr_status_position_y;
        animation = g_debugchr_status_animation;
        offset_index = 0;
        __asm__("" : "=r"(offset_index) : "0"(offset_index));
        one = (s32)g_debugchr_status_y_offsets;
        stack.group_y_offset = (const u16*)one;
        do {
            group_id = g_debugchr_status_group_ids[group_index];
            last_status = g_debugchr_status_group_bounds[group_id + 1];
            start_status = g_debugchr_status_group_bounds[group_id];
            __asm__("" : : "r"(last_status), "r"(start_status));
            status_count = last_status - start_status;
            stack.first_status = start_status;

            frame = *animation;
            if (frame != 0xff) {
                if ((u32)frame >= 0x41) {
                    updated_frame = frame + 0xfe;
                    __asm__("" : "=r"(updated_frame) : "0"(updated_frame));
                    *animation = updated_frame;
                } else if ((u32)frame >= 0x0b) {
                    updated_frame = frame - 1;
                    *animation = updated_frame;
                    if (*animation == 0x0b) {
                        __asm__ volatile("" : : : "memory");
                        one = 1;
                        *animation = one;
                    }
                } else if ((u32)frame >= 2) {
                    updated_frame = frame - 1;
                    *animation = updated_frame;
                    one = 1;
                    if (*animation == one) {
                        *animation = 0;
                    }
                }
            }
            __asm__("" : : "r"(offset_index));

            status_index = 0;
            if (status_count > 0) {
                y_offset = stack.group_y_offset;
                poly_tail = (u8*)current_poly + 0x22;
                do {
                    battle_make_default_poly_ft4(current_poly);
                    __asm__("" : "=r"(offset_index) : "0"(offset_index));
                    geometry_poly = (u8*)current_poly;
                    texture = &g_debugchr_status_texture;
                    __asm__("" : : "r"(geometry_poly), "r"(texture));
                    temp_v1 = (u32)&g_debugchr_status_scales[0][0];
                    one = stack.first_status;
                    temp_a3 = *y_offset;
                    status_id = one + status_count;
                    __asm__("" : "=r"(status_id) : "0"(status_id));
                    status_id -= status_index;
                    __asm__("" : "=r"(status_id) : "0"(status_id));
                    scale = (const s16*)(temp_v1 + status_id * 4);
                    /* This block is the six-argument call
                     *   debugchr_set_scaled_poly_ft4_geometry(poly, &texture, position_y - 1,
                     *       uv_rects[status_id], scales[status_id],
                     *       (u8 *)offsets + offset_index)
                     * with `*position_y += *y_offset` in the jal delay slot. Written
                     * as plain C it compiles to exactly 700 bytes with the identical
                     * instruction stream, but GCC hoists the offsets `la/addu` out of
                     * the inner loop (offset_index is loop-invariant there; a zero-byte
                     * `__asm__("" : "=r"(offset_index) : "0"(offset_index))` in the loop
                     * stops that) and then assigns s2/s3, s4..s8 in a different order
                     * (pinning any of them frees a register that GCC fills with the
                     * hoisted constant 1, which the retail build keeps in t0). Only the
                     * callee-saved register assignment remains unmatched. */
                    __asm__ volatile(
                        "sw $2,0x10($29)\n"
                        "lui $2,%%hi(g_debugchr_status_offsets)\n"
                        "addiu $2,$2,%%lo(g_debugchr_status_offsets)\n"
                        "lhu $3,0($22)\n"
                        "addu $2,$30,$2\n"
                        "sw $2,0x14($29)\n"
                        "lui $2,%%hi(g_debugchr_status_uv_rects)\n"
                        "addiu $2,$2,%%lo(g_debugchr_status_uv_rects)\n"
                        "addu $3,$3,$7\n"
                        "sll $7,$6,1\n"
                        "addu $7,$7,$6\n"
                        "sll $7,$7,2\n"
                        "addiu $6,$22,-2\n"
                        "addu $7,$7,$2\n"
                        "\t.set\tnoreorder\n"
                        "\t.set\tnomacro\n"
                        "\tjal debugchr_set_scaled_poly_ft4_geometry\n"
                        "\tsh $3,0($22)\n"
                        "\t.set\tmacro\n"
                        "\t.set\treorder\n"
                        : "=r"(scale), "=r"(status_id), "=r"(temp_a3),
                        "=r"(temp_v1)
                        : "0"(scale), "1"(status_id), "2"(temp_a3)
                        : "$31", "memory");
                    *position_y -= *y_offset;

                    frame = *animation;
                    if (frame == 0x40) {
                        poly_tail[-0x1e] = 0x80;
                        poly_tail[-0x1d] = 0x80;
                        poly_tail[-0x1c] = 0x80;
                        *animation = 0;
                    }

                    palette_frame = *animation;
                    __asm__ volatile("" : : : "memory");
                    if ((palette_frame == 0) || ((active_frame = (u32)palette_frame < 0x40) == 0)) {
                        *(s16*)(poly_tail - 0x14) = 0x7d7c;
                    } else {
                        one = 1;
                        if (palette_frame == one) {
                            *(s16*)(poly_tail - 0x14) = 0x7dfc;
                        } else if (active_frame != 0) {
                            x0 = *(u16*)(poly_tail - 0x18);
                            x1 = *(u16*)(poly_tail - 0x10);
                            *(s16*)(poly_tail - 0x14) = 0x7e7c;
                            __asm__ volatile("" : : : "memory");
                            x2 = *(u16*)(poly_tail - 8);
                            x3 = *(u16*)poly_tail;
                            x0++;
                            x1++;
                            x2++;
                            x3++;
                            *(u16*)(poly_tail - 0x18) = x0;
                            *(u16*)(poly_tail - 0x10) = x1;
                            *(u16*)(poly_tail - 8) = x2;
                            *(u16*)poly_tail = x3;
                        }
                    }

                    SetSemiTrans(current_poly, 1);
                    SetShadeTex(current_poly, 0);
                    submit_primitive(current_poly);
                    poly_tail += sizeof(POLY_FT4);
                    status_index++;
                    current_poly++;
                } while (status_index < status_count);
            }

            animation++;
            offset_index += 12;
            __asm__("" : "=r"(offset_index) : "0"(offset_index));
            group_index++;
            one = (s32)stack.group_y_offset;
            one += 4;
            continue_groups = group_index < g_debugchr_status_group_count;
            ((DebugChrStatusRenderStack*)&stack)->group_y_offset = (const u16*)one;
        } while (continue_groups);
    }
}
