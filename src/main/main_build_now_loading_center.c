#include "psx/types.h"

extern void build_now_loading(u32, u32, u32);

void main_build_now_loading_center(u32 arg0) {
    build_now_loading(arg0, 0x80, 0);
}
