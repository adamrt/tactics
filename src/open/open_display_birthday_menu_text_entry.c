#include "psx/types.h"

typedef struct OpenBirthdayTextPosition {
    s16 x;
    s16 y;
    s32 unused;
    s32 record_height;
} OpenBirthdayTextPosition;

void battle_world_display_menu_text_entry(s32 combined_text_index, void* image,
    OpenBirthdayTextPosition* position);

void open_display_birthday_menu_text_entry(s32 record_index,
    s32 combined_text_index, s16 x,
    s16 y, void* image) {
    s32 record_value;
    s32 call_text;
    void* call_image;
    OpenBirthdayTextPosition position;

    record_value = record_index * 56;
    __asm__ volatile(
        "sw $6,0x30($29)\n"
        "sw $7,0x34($29)");
    position.x = x;
    position.y = y;
    __asm__ volatile(
        ".set noat\n"
        "lui $1,0x8008\n"
        "addiu $1,$1,0x60c8\n"
        "addu $1,$1,%0\n"
        "lh %0,0($1)\n"
        ".set at"
        : "=r"(record_value)
        : "0"(record_value)
        : "$1");
    call_text = combined_text_index;
    __asm__ volatile("" : "=r"(call_text) : "0"(call_text));
    position.record_height = record_value;
    __asm__ volatile("lw %0,0x38($29)" : "=r"(call_image));
    battle_world_display_menu_text_entry(call_text, call_image, &position);
}
