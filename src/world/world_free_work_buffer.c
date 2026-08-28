#include "psx/types.h"

extern void* D_801CD1EC;
extern void main_game_free(void* ptr);

void world_free_work_buffer(void) {
    main_game_free(D_801CD1EC);
}
