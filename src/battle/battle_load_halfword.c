#include "psx/types.h"

s16 battle_load_halfword(u8* data) {
    return (s16)(data[0] | (data[1] << 8));
}
