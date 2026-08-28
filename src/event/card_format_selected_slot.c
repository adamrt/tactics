#include "psx/types.h"

extern u8 g_card_selected_slot;
extern const char g_card_slot_0_path[];
extern const char g_card_slot_1_path[];
extern s32 card_wait_for_operation_result(s32 retry_limit);
extern char* strcpy(char* destination, const char* source);
extern s32 FileFormat(const char* path);

s32 card_format_selected_slot(void) {
    s32 result;
    char path[8];

    result = card_wait_for_operation_result(10);
    if (result > 0)
        return 0;
    if (g_card_selected_slot == 0)
        strcpy(&path[0], g_card_slot_0_path);
    else
        strcpy(&path[0], g_card_slot_1_path);
    result = FileFormat(&path[0]);
    result = FileFormat(&path[0]);
    result = FileFormat(&path[0]);
    return result;
}
