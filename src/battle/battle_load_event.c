#include "psx/types.h"

extern void (*g_call_inner_subroutine_target)(void);
extern u32* D_80173CA4;
extern u32* g_battle_text_pointers;
extern u8 D_8004A6BC[];

extern void switch_to_next_thread(void);
extern s32 call_inner_subroutine();
extern void main_load_data_from_disc(void);
extern void main_check_file_still_loading(void);

void battle_load_event(s32 id) {
    u32* p;
    u32 off;

    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = main_load_data_from_disc;
    } while (call_inner_subroutine(id * 4 + 0xE7B, 0x2000, D_8004A6BC) != 0);

    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = main_check_file_still_loading;
    } while (call_inner_subroutine() != 0);

    p = D_80173CA4;
    off = *p;
    if (off != 0xF2F2F2F2) {
        g_battle_text_pointers = (u32*)(off + (u32)p);
        *p = 0xF2F2F2F2;
    }
}
