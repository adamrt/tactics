#include "psx/types.h"

extern void* memset(void* destination, s32 value, u32 size);
extern u8 g_card_state_801c9570;
extern s16 g_card_state_801c9572;
extern s16 g_card_state_801c9574;
extern s16 g_card_state_801c9576;
extern s16 g_card_state_801c9578;
extern s16 g_card_state_801c957c;
extern u8 g_card_save_buffer[0x1e80];
extern u8* g_card_save_buffer_pointer;

void card_initialize_save_menu_state(void) {
    g_card_state_801c9574 = 0x18;
    g_card_state_801c9572 = 0;
    g_card_state_801c9578 = 0;
    g_card_state_801c9576 = 0;
    g_card_state_801c9570 = 0;
    g_card_state_801c957c = 0;
    g_card_save_buffer_pointer = g_card_save_buffer;
    memset(g_card_save_buffer_pointer, 0xff, 0x1e80);
}
