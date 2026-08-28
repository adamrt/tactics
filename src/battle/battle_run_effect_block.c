#include "psx/types.h"

typedef struct EffectStateRecord {
    u8 pad0[6];      /* 0x00 */
    s16 pc;          /* 0x06 */
    u16* script;     /* 0x08 */
    u8 pad_c[236];   /* 0x0C */
} EffectStateRecord; /* 0xF8 */

extern EffectStateRecord g_effect_state_records[];
extern s16 (*g_effect_instructions[])(EffectStateRecord*);

s32 battle_run_effect_block(s16 index) {
    EffectStateRecord* rec;
    s16 result;

    rec = &g_effect_state_records[index];
    for (;;) {
        result = g_effect_instructions[*(u16*)((u8*)rec->script + rec->pc) & 0x1FF](rec);
        if (result == 2) {
            return 0;
        }
        if (result == 0) {
            return 1;
        }
    }
}
