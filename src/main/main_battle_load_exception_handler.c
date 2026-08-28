#include "psx/types.h"

extern void main_malloc_exception_handler(s32, s32);

void main_battle_load_exception_handler(s32 value) {
    main_malloc_exception_handler(3, value);
}
