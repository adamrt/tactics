#include "psx/types.h"

typedef struct OpenPoint32 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} OpenPoint32;

extern s16 D_80085578;
extern s16 D_8008557A;
extern s16 D_8008557C;
extern s16 D_8008557E;
extern s16 D_80085582;
extern s16 D_80085584;
extern s16 D_80085586;
extern void* D_80085588;
extern void* D_80085594;

extern s16 D_800852E8;
extern s16 D_800852EA;
extern s16 D_800852EC;
extern s16 D_800852EE;
extern s16 D_800852F0;
extern s16 D_800852F2;
extern s16 D_800852F4;
extern s16 D_800852F6;
extern s16 D_800852F8;
extern s16 D_800852FA;
extern s16 D_800852FC;
extern s16 D_800852FE;
extern s16 D_80085300;
extern s16 D_80085302;
extern s16 D_80085304;
extern s16 D_80085306;
extern s16 D_80085308;
extern void* D_8008530C;
extern s16 D_80085314;
extern void* D_80085318;
extern void* D_8008531C;
extern s16 D_80085320;
extern s16 D_80085322;

extern s32 D_8008E434;
extern s32 D_800855F4;
extern s32 D_80073FB4;
extern s32 D_8008FC0C;
extern s32 D_801097DC;

extern void world_initialize_thread(s32 thread_id, void* entry);
extern void world_store_thread_function_parameters(s32 thread_id, void* args, s32 arg2, s32 arg3);

void open_bin_0006cbf8_0006cdb0(s32 thread_id, s32 limit, const OpenPoint32* extent, const OpenPoint32* origin) {
    s16* state = &D_80085578;
    s16* prim = &D_800852E8;
    s32 width;
    s32 height;
    s32 height2;
    s32 bottom;
    void* entry;
    s32 hundred;
    s32 one;
    s32 ox;
    s32 oy;
    s32 ey;

    width = extent->x;
    height = extent->y;
    *state = height;
    __asm__ volatile("" ::: "memory");
    height2 = extent->y;
    D_8008557E = 4;
    D_8008557C = 4;
    D_80085584 = 2;
    D_80085586 = 2;
    D_80085588 = &D_8008E434;
    D_80085594 = &D_800855F4;
    D_80085582 = 0;
    *prim = 0x200;
    __asm__ volatile("");
    hundred = 0x100;
    __asm__ volatile("" : "=r"(hundred) : "0"(hundred));
    width = (width + 0x18) & 0xFFFC;
    D_800852EA = hundred;
    D_800852EC = width;
    D_800852EE = 0;
    __asm__ volatile("");
    D_8008557A = limit - height2;
    __asm__ volatile("");
    ox = origin->x;
    __asm__ volatile("");
    D_800852F0 = ox - 0x80;
    __asm__ volatile("");
    oy = origin->y;
    __asm__ volatile("");
    entry = &D_801097DC;
    __asm__ volatile("" : "=r"(entry) : "0"(entry));
    bottom = oy - 0x78;
    D_800852F4 = width;
    D_800852F6 = 0;
    D_800852F8 = 0;
    D_800852FA = 0;
    D_800852FC = width;
    D_800852FE = 0;
    D_80085300 = 0;
    D_80085302 = 0;
    D_80085304 = 0;
    D_800852F2 = bottom;
    __asm__ volatile("");
    ey = extent->y;
    __asm__ volatile("");
    D_80085308 = 0;
    D_8008530C = &D_80073FB4;
    __asm__ volatile("");
    one = 1;
    __asm__ volatile("" : "=r"(one) : "0"(one));
    D_80085306 = ey;
    __asm__ volatile("");
    D_80085314 = one;
    D_80085318 = state;
    D_8008531C = &D_8008FC0C;
    D_80085320 = 0;
    D_80085322 = 0;

    world_initialize_thread(thread_id, entry);
    world_store_thread_function_parameters(thread_id, prim, 0, 0);
}
