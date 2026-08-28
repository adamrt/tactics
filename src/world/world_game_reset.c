#include "psx/types.h"

extern void main_game_reset(void);

void world_game_reset(void) {
    main_game_reset();
}
