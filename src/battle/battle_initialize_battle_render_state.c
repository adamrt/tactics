typedef signed short s16;
typedef signed int s32;

typedef struct BattleMiscSlot {
    char _pad000[0x43c];
    char init_byte;
    char _pad43d[3];
} BattleMiscSlot;

extern s16 g_battle_projection_scale;
extern s16 g_battle_gte_rtps_vz0;
extern s16 g_battle_gte_rtpt_vz2;
extern s16 g_battle_gte_rtpt_vz1;
extern s16 g_battle_gte_rtpt_vz0;
extern s16 g_battle_sprite_transform_m21;
extern s16 g_battle_sprite_transform_m20;
extern s16 g_battle_sprite_transform_m12;
extern s16 g_battle_sprite_transform_m02;
extern s32 g_battle_sprite_transform_tz;
extern s16 g_battle_gfx_counter;
extern s16 g_battle_previous_gfx_counter;
extern s16 D_800b6290;
extern s16 D_800b628c;
extern BattleMiscSlot g_battle_misc_data[16];
extern void* g_last_misc_unit_init_byte;

void battle_initialize_battle_render_state(void) {
    g_battle_projection_scale = 0x1000;
    g_battle_gte_rtps_vz0 = 0x200;
    g_battle_gte_rtpt_vz2 = 0x200;
    g_battle_gte_rtpt_vz1 = 0x200;
    g_battle_gte_rtpt_vz0 = 0x200;
    g_battle_sprite_transform_m21 = 0;
    g_battle_sprite_transform_m20 = 0;
    g_battle_sprite_transform_m12 = 0;
    g_battle_sprite_transform_m02 = 0;
    g_battle_sprite_transform_tz = 0;
    g_battle_gfx_counter = 0;
    g_battle_previous_gfx_counter = 0;
    D_800b6290 = 0;
    D_800b628c = 0;
    g_last_misc_unit_init_byte = &g_battle_misc_data[15].init_byte;
}
