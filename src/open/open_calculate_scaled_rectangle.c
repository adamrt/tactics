#include "psx/types.h"

typedef struct OpenPoint {
    u16 unused_00;
    u16 unused_02;
    u16 x;
    u16 y;
} OpenPoint;

typedef struct OpenRectangle {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} OpenRectangle;

void open_calculate_scaled_rectangle(
    s32 scale_mode,
    const OpenPoint* point,
    OpenRectangle* rectangle) {
    register const OpenPoint* input __asm__("$7") = point;
    OpenRectangle* output = rectangle;
    s32 scale;
    register s32 shifted_x __asm__("$5");
    register s32 shifted_y __asm__("$7");
    register s32 x __asm__("$6");
    register s32 y __asm__("$8");
    s32 scaled_x;
    register s32 scaled_y __asm__("$4");
    s32 height;

    switch (scale_mode) {
    case 0:
        scale = 20;
        break;
    case 1:
        scale = 50;
        break;
    case 2:
        scale = 80;
        break;
    case 3:
        scale = 90;
        break;
    default:
        scale = 100;
        break;
    }

    shifted_x = input->x << 16;
    x = shifted_x >> 16;
    scaled_x = x * scale;
    shifted_y = input->y << 16;
    y = shifted_y >> 16;
    scaled_y = y * scale;
    __asm__ volatile(
        "lui $2,0x51eb\n"
        "ori $2,$2,0x851f\n"
        "mult $3,$2\n"
        "mfhi $9\n"
        "srl $5,$5,31\n"
        "addu $6,$6,$5\n"
        "mult $4,$2\n"
        "sra $6,$6,1\n"
        "andi $6,$6,0xfffc\n"
        "srl $7,$7,31\n"
        "addu $8,$8,$7\n"
        "sra $8,$8,1\n"
        "sra $3,$3,31\n"
        "sra $2,$9,6\n"
        "subu $2,$2,$3\n"
        "andi $9,$2,0xfffc\n"
        "sra $4,$4,31\n"
        "mfhi $10\n"
        "sra $2,$10,6\n"
        "subu $2,$2,$4\n"
        "andi $3,$2,0xfffc\n"
        "slt $2,$6,$9\n"
        "beqz $2,1f\n"
        "andi $8,$8,0xfffc\n"
        "move $9,$6\n"
        "1:\n"
        "slt $2,$8,$3\n"
        "beqz $2,2f\n"
        "subu $2,$6,$9\n"
        "move $3,$8\n"
        "2:\n"
        "sh $2,0($11)\n"
        "subu $2,$8,$3\n"
        "sh $2,2($11)\n"
        "sll $2,$9,1\n"
        "sh $2,4($11)\n"
        "sll $2,$3,1"
        : "=r"(scaled_x), "=r"(height)
        : "0"(scaled_x), "r"(shifted_x), "r"(shifted_y), "r"(x), "r"(y),
        "r"(scaled_y), "r"(output)
        : "$9", "$10", "memory");
    output->height = height;
}
