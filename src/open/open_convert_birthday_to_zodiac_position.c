#include "psx/types.h"

extern const u8 g_open_month_lengths[12];
extern const u8 g_open_zodiac_months[12][2];
extern const u8 g_open_zodiac_days[12][2];

void open_convert_birthday_to_zodiac_position(s32* month, s32* day) {
    register s32* month_pointer __asm__("$10") = month;
    s32* day_pointer = day;
    register const u8(*zodiac_months)[2] __asm__("$8") = g_open_zodiac_months;
    register s32 index __asm__("$6");
    s32 month_value;
    s32 first_month;

    first_month = zodiac_months[0][0];
    month_value = *month_pointer;
    index = 0;
    if (first_month != month_value) {
        __asm__ volatile(
            ".set noreorder\n"
            ".set noat\n"
            "lui $9,0x2aaa\n"
            "ori $9,$9,0xaaab\n"
            "addu $7,%1,$0\n"
            "1:\n"
            "addiu $4,%0,1\n"
            "mult $4,$9\n"
            "sra $2,$4,31\n"
            "mfhi $11\n"
            "sra $3,$11,1\n"
            "subu %0,$3,$2\n"
            "sll $2,%0,1\n"
            "addu $2,$2,%0\n"
            "sll $2,$2,2\n"
            "subu %0,$4,$2\n"
            "sll $2,%0,1\n"
            "addu $2,$2,%2\n"
            "lbu $2,0($2)\n"
            "nop\n"
            ".word 0x1447fff2\n"
            "addiu $4,%0,1\n"
            ".set at\n"
            ".set reorder"
            : "=r"(index)
            : "r"(month_value), "r"(zodiac_months), "0"(index)
            : "memory");
    }

    {
        const u8(*zodiac_days)[2] = g_open_zodiac_days;

        /* Keep noreorder active through the compiler-emitted return. */
        __asm__ volatile(
            ".set noreorder\n"
            ".set noat\n"
            "sll $2,$6,1\n"
            "addu $4,$2,$7\n"
            "lbu $3,0($4)\n"
            "lw $2,0($5)\n"
            "nop\n"
            "slt $2,$2,$3\n"
            ".word 0x1040001d\n"
            "lui $2,0x2aaa\n"
            "ori $2,$2,0xaaab\n"
            "addiu $3,$6,11\n"
            "mult $3,$2\n"
            "sra $2,$3,31\n"
            "mfhi $11\n"
            "sra $4,$11,1\n"
            "subu $6,$4,$2\n"
            "sll $2,$6,1\n"
            "addu $2,$2,$6\n"
            "sll $2,$2,2\n"
            "subu $6,$3,$2\n"
            "addiu $2,$6,1\n"
            "sw $2,0($10)\n"
            "sll $2,$6,1\n"
            "addu $3,$7,$2\n"
            "addu $2,$2,$7\n"
            "lbu $3,-1($3)\n"
            "lbu $4,0($2)\n"
            "lui $1,0x8007\n"
            "addiu $1,$1,0x3f33\n"
            "addu $1,$1,$3\n"
            "lbu $2,0($1)\n"
            "lw $3,0($5)\n"
            "subu $2,$2,$4\n"
            "addiu $4,$2,1\n"
            "addu $3,$3,$4\n"
            ".word 0x0801a151\n"
            "sw $3,0($5)\n"
            "addiu $2,$6,1\n"
            "sw $2,0($10)\n"
            "lbu $3,0($4)\n"
            "lw $2,0($5)\n"
            "nop\n"
            "subu $2,$2,$3\n"
            "addiu $2,$2,1\n"
            "sw $2,0($5)\n"
            ".set at"
            :
            : "r"(index), "r"(zodiac_days), "r"(month_pointer),
            "r"(day_pointer)
            : "memory");
    }
}
