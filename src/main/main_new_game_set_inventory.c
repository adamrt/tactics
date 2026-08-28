#include "psx/types.h"

enum {
    INVENTORY_SIZE = 0x100,
    POTION = 0xf0,
    HI_POTION,
    X_POTION,
    ETHER,
    HI_ETHER,
    ELIXIR,
    ANTIDOTE,
    EYE_DROPS,
    ECHO_GRASS,
    MAIDENS_KISS,
    SOFT,
    HOLY_WATER,
    REMEDY,
    PHOENIX_DOWN,
};

extern u8 g_inventory[INVENTORY_SIZE];

void main_new_game_set_inventory(void) {
    int remaining = INVENTORY_SIZE - 1;
    u8* item = &g_inventory[INVENTORY_SIZE - 1];

    do {
        *item = 0;
        remaining--;
        item--;
    } while (remaining >= 0);

    g_inventory[POTION] = 5;
    g_inventory[HI_POTION] = 2;
    g_inventory[X_POTION] = 1;
    g_inventory[ETHER] = 1;
    g_inventory[HI_ETHER] = 1;
    g_inventory[ELIXIR] = 1;
    g_inventory[ANTIDOTE] = 1;
    g_inventory[EYE_DROPS] = 2;
    g_inventory[ECHO_GRASS] = 1;
    g_inventory[MAIDENS_KISS] = 1;
    g_inventory[SOFT] = 1;
    g_inventory[HOLY_WATER] = 1;
    g_inventory[REMEDY] = 1;
    g_inventory[PHOENIX_DOWN] = 2;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
