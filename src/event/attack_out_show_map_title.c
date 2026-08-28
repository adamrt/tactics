#include "psx/types.h"

typedef struct AttackMapTitleSprite {
    u8 reserved_00[0xd0];
} AttackMapTitleSprite;

extern AttackMapTitleSprite g_attack_map_title_sprites[];
extern s32 D_801cd054;

extern s32 battle_get_third_thread_parameter(void);
extern void func_801C992C(AttackMapTitleSprite* sprite, s32 y, s32 arg2,
    s32 arg3);
extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);

void attack_out_show_map_title(void) {
    s32 step;
    s32 slot;
    s32 y;

    step = battle_get_third_thread_parameter();
    slot = 0;
    if (step == 0) {
        step = 1;
    }

    y = 8;
    do {
        slot ^= 1;
        func_801C992C(&g_attack_map_title_sprites[slot], y, 0x80, 0);
        y += step;
        switch_to_next_event_thread();
    } while (y < 0xf8);

    y = 0;
    do {
        slot ^= 1;
        func_801C992C(&g_attack_map_title_sprites[slot], 0xf8, 0x80, 0);
        y += step;
        switch_to_next_event_thread();
    } while (y < 0x6e);

    y = 8;
    do {
        slot ^= 1;
        func_801C992C(&g_attack_map_title_sprites[slot], y, 0x80, 1);
        if (y >= 0x81) {
            D_801cd054 = 1;
        }
        y += step;
        switch_to_next_event_thread();
    } while (y < 0xf9);

    stop_current_event_thread();
}
