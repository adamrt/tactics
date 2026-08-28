#include "psx/types.h"
typedef struct {
    u8 lo;
    u8 hi;
} Pair;
extern Pair D_8018D7FC[];
void world_get_item_type_icon_rect(s32 index, s16* out) {
    out[0] = D_8018D7FC[index].lo;
    out[1] = D_8018D7FC[index].hi;
    out[2] = 0xC;
    out[3] = 0xC;
}
