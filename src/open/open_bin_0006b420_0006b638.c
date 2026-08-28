#include "psx/gpu.h"
#include "psx/types.h"

typedef struct OpenNewGameState {
    /* 0x00 */ u8 unused_00[0x10];
    /* 0x10 */ s32 step;
    /* 0x14 */ u8 unused_14[0x0c];
    /* 0x20 */ s32 name_text_id;
} OpenNewGameState;

typedef struct OpenPartyNameBlock {
    /* 0x00 */ char name[16];
} OpenPartyNameBlock;

typedef struct OpenPartyRecord {
    /* 0x00 */ u8 unused_00[0xbe];
    /* 0xbe */ char name[16];
} OpenPartyRecord;

extern s32 g_open_overlay_fade_flags;
extern s32 g_open_current_openbk_image_id;
extern s32 g_open_current_controller_index;
extern u32* g_open_file_destination;
extern s32 g_open_display_buffer_index;

extern void func_80043F50(void);
extern void open_start_controller_7_with_openbk(void);
extern void open_prepare_new_game_party(s32 slot, s32 flags);
extern void func_801063AC(void);
extern void* world_find_text_entry(s32 id);
extern OpenPartyNameBlock* func_80139184(void* text, u32* destination);
extern OpenPartyRecord* main_get_party_data_pointer(s32 index);
extern void func_8006B63C(void);
extern s32 func_8006D7F4(void);
extern void open_noop_8006d7ec(void);

void open_bin_0006b420_0006b638(OpenNewGameState* state) {
    RECT rect;
    OpenPartyNameBlock* name;
    OpenPartyRecord* party;

    if (state->step == 5) {
        if (g_open_overlay_fade_flags & 4) {
            return;
        }
        func_80043F50();
        g_open_current_controller_index -= 1;
        open_start_controller_7_with_openbk();
        return;
    }

    if (state->step == 4) {
        open_prepare_new_game_party(0, 0);
        func_801063AC();

        if (g_open_display_buffer_index != 0) {
            rect.x = 0;
            rect.y = 0;
            rect.w = 0x100;
            rect.h = 0xF0;
        } else {
            rect.x = 0;
            rect.y = 0xF0;
            rect.w = 0x100;
            rect.h = 0xF0;
        }
        StoreImage(&rect, g_open_file_destination);
        DrawSync(0);

        if (g_open_display_buffer_index == 0) {
            rect.x = 0;
            rect.y = 0;
            rect.w = 0x100;
            rect.h = 0xF0;
        } else {
            rect.x = 0;
            rect.y = 0xF0;
            rect.w = 0x100;
            rect.h = 0xF0;
        }
        LoadImage(&rect, g_open_file_destination);
        DrawSync(0);

        g_open_current_openbk_image_id = -1;
        name = func_80139184(world_find_text_entry(0x4000), g_open_file_destination);
        party = main_get_party_data_pointer(0);
        *(OpenPartyNameBlock*)party->name = *name;
        g_open_current_controller_index -= 1;
        func_8006B63C();
        return;
    }

    if (g_open_overlay_fade_flags & 4) {
        return;
    }
    if (func_8006D7F4() != 0) {
        return;
    }
    open_noop_8006d7ec();
    state->step = 4;
}
