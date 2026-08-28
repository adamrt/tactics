#include "fft/opening.h"

extern void StCdInterrupt(void);
extern void DecDCTout(void* output, s32 words);
extern s32 g_st_cd_interrupt_pending;
extern void* g_open_mdec_output_buffers[2];
extern volatile s32 g_open_mdec_output_buffer_index;
extern volatile RECT g_open_mdec_frame_rects[];
extern volatile s32 g_open_mdec_frame_position_index;
extern RECT g_open_mdec_output_rect;
extern u16 g_open_mdec_slice_width;
extern s16 g_open_mdec_slice_height;
extern volatile s32 g_open_mdec_output_ready;

void open_handle_mdec_output_slice(void) {
    RECT* output_rect;
    void** output_buffers;
    s32 output_buffer_index;
    s32 frame_position_index;
    s32 current_output_buffer_index;
    u16 slice_width;
    s32 output_x_before_frame_end;

    if (g_st_cd_interrupt_pending != 0) {
        StCdInterrupt();
        g_st_cd_interrupt_pending = 0;
    }
    __asm__ volatile(
        "lui %0,%%hi(g_open_mdec_output_rect)\n"
        "addiu %0,%0,%%lo(g_open_mdec_output_rect)"
        : "=r"(output_rect));
    current_output_buffer_index = g_open_mdec_output_buffer_index;
    __asm__ volatile("addiu %0,%1,-32"
        : "=r"(output_buffers)
        : "r"(output_rect));
    LoadImage(output_rect, output_buffers[current_output_buffer_index]);
    /* Preserve the callback's tightly scheduled output-buffer state update. */
    __asm__ volatile(
        ".set noat\n"
        "lui $3,%%hi(g_open_mdec_output_buffer_index)\n"
        "lw $3,%%lo(g_open_mdec_output_buffer_index)($3)\n"
        "lhu $2,0($16)\n"
        "lui $5,%%hi(g_open_mdec_slice_width)\n"
        "lhu $5,%%lo(g_open_mdec_slice_width)($5)\n"
        "sltiu $7,$3,1\n"
        "addu $2,$2,$5\n"
        "lui $1,%%hi(g_open_mdec_output_buffer_index)\n"
        "sw $7,%%lo(g_open_mdec_output_buffer_index)($1)\n"
        "sh $2,0($16)\n"
        "lui $6,%%hi(g_open_mdec_frame_position_index)\n"
        "lw $6,%%lo(g_open_mdec_frame_position_index)($6)\n"
        "sll $2,$2,16\n"
        ".set at"
        : "=r"(output_x_before_frame_end), "=r"(slice_width),
        "=r"(output_buffer_index), "=r"(frame_position_index)
        :
        : "$1", "$3", "memory");
    /* Keep the independently addressed frame-coordinate tables visible. */
    __asm__ volatile(
        ".set noat\n"
        "sll $4,$6,3\n"
        "lui $1,%%hi(g_open_mdec_frame_rects)\n"
        "addiu $1,$1,%%lo(g_open_mdec_frame_rects)\n"
        "addu $1,$1,$4\n"
        "lh $3,0($1)\n"
        "lui $1,%%hi(g_open_mdec_frame_rects + 4)\n"
        "addiu $1,$1,%%lo(g_open_mdec_frame_rects + 4)\n"
        "addu $1,$1,$4\n"
        "lh $4,0($1)\n"
        "sra $2,$2,16\n"
        "addu $3,$3,$4\n"
        "slt $2,$2,$3\n"
        ".set at"
        : "=r"(output_x_before_frame_end)
        : "0"(output_x_before_frame_end), "r"(frame_position_index)
        : "$1", "$3", "$4", "memory");
    /* The callback's two tails share a branch-delay-sensitive schedule. */
    __asm__ volatile(
        ".set noreorder\n"
        ".word 0x1040000f\n" /* beqz $2, completed frame */
        "sll $5,$5,16\n"
        "lui $2,%%hi(g_open_mdec_slice_height)\n"
        "lh $2,%%lo(g_open_mdec_slice_height)($2)\n"
        "sra $5,$5,16\n"
        "mult $5,$2\n"
        "sll $2,$7,2\n"
        "addu $2,$2,$17\n"
        "lw $4,0($2)\n"
        "mflo $5\n"
        "srl $2,$5,31\n"
        "addu $5,$5,$2\n"
        ".word 0x0c01cd9d\n" /* jal DecDCTout */
        "sra $5,$5,1\n"
        ".word 0x08019e45\n" /* j shared epilogue */
        "nop\n"
        "1:\n"
        ".set noat\n"
        "li $2,1\n"
        "lui $1,%%hi(g_open_mdec_output_ready)\n"
        "sw $2,%%lo(g_open_mdec_output_ready)($1)\n"
        "sltiu $2,$6,1\n"
        "lui $1,%%hi(g_open_mdec_frame_position_index)\n"
        "sw $2,%%lo(g_open_mdec_frame_position_index)($1)\n"
        "sll $2,$2,3\n"
        "lui $1,%%hi(g_open_mdec_frame_rects)\n"
        "addiu $1,$1,%%lo(g_open_mdec_frame_rects)\n"
        "addu $1,$1,$2\n"
        "lhu $3,0($1)\n"
        "nop\n"
        "sh $3,0($16)\n"
        "lui $1,%%hi(g_open_mdec_frame_rects + 2)\n"
        "addiu $1,$1,%%lo(g_open_mdec_frame_rects + 2)\n"
        "addu $1,$1,$2\n"
        "lhu $2,0($1)\n"
        "nop\n"
        "lui $1,%%hi(g_open_mdec_output_rect)\n"
        "sh $2,%%lo(g_open_mdec_output_rect + 2)($1)\n"
        ".set at\n"
        "2:"
        :
        : "r"(output_x_before_frame_end), "r"(output_buffers),
        "r"(output_buffer_index), "r"(slice_width),
        "r"(output_rect), "r"(frame_position_index)
        : "$1", "$2", "$3", "$4", "$5", "memory");
}
