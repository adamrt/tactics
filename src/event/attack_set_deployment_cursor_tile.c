#include "psx/types.h"

extern s32 g_attack_deployment_cursor_column;
extern s32 g_attack_deployment_cursor_row;

void attack_set_deployment_cursor_tile(s32 column, s32 row) {
    g_attack_deployment_cursor_column = column;
    g_attack_deployment_cursor_row = row;
}
