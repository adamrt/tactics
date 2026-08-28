#include "psx/types.h"

typedef struct CardImageRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} CardImageRect;

typedef struct CardSaveSlotText {
    u8 data[0x50];
} CardSaveSlotText;

extern CardSaveSlotText g_card_save_slot_descriptions[];
extern const u16 g_card_save_slot_text_row_ids[];

extern void card_render_text_id_rows_to_vram(const CardSaveSlotText* text,
    const u16* row_ids,
    const CardImageRect* rect,
    s32 unused);

void card_render_save_slot_text(s32 slot) {
    CardImageRect rect;

    if (slot < 6) {
        rect.x = 0x100;
        rect.y = slot * 0x20 + 0x30;
        rect.w = 0x32;
        rect.h = 0x20;
    } else if (slot < 11) {
        rect.x = 0x1c0;
        rect.y = (slot - 6) * 0x20 + 0x40;
        rect.w = 0x32;
        rect.h = 0x20;
    } else {
        rect.x = 0x180;
        rect.y = (slot - 11) * 0x20 + 0x60;
        rect.w = 0x32;
        rect.h = 0x20;
    }
    card_render_text_id_rows_to_vram(&g_card_save_slot_descriptions[slot], g_card_save_slot_text_row_ids, &rect,
        0);
}
