#include "psx/types.h"

extern u8 g_attack_deployed_roster_id_by_tile[5][5];
extern u8 g_attack_deployed_units_by_squad[4][25];

void attack_reset_deployment_tables(void) {
    s32 row;
    s32 column;

    row = 0;
    do {
        column = 4;
        do {
            g_attack_deployed_roster_id_by_tile[row][column] = 0xff;
            column--;
        } while (column >= 0);
        row++;
    } while (row < 5);

    row = 0;
    do {
        column = 24;
        do {
            g_attack_deployed_units_by_squad[row][column] = 0xff;
            column--;
        } while (column >= 0);
        row++;
    } while (row < 4);
}
