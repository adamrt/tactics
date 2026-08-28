#include "psx/types.h"

extern s32 g_card_open_descriptor;
extern const char g_card_slot_0_path[];
extern const char g_card_slot_1_path[];

extern s32 card_get_selected_slot(void);
extern s32 card_close_file_with_retries(s32 descriptor);
extern s32 card_wait_for_operation_result(s32 retry_limit);
extern char* strcpy(char* destination, const char* source);
extern char* strcat(char* destination, const char* source);
extern s32 FileOpen(const char* path, s32 mode);

s32 card_open_selected_file_with_retries(const char* filename, s32 mode) {
    s32 i;
    s32 result;
    char path[128];

    i = 0;
    if (g_card_open_descriptor >= 0) {
        result = card_close_file_with_retries(g_card_open_descriptor);
        if (result == 0) {
            return -2;
        }
    }

    if (card_get_selected_slot() == 0) {
        strcpy(path, g_card_slot_0_path);
    } else {
        strcpy(path, g_card_slot_1_path);
    }
    strcat(path, filename);

    while (i < 40) {
        result = card_wait_for_operation_result(10);
        if (result != 0) {
            return -2;
        }
        g_card_open_descriptor = FileOpen(path, mode);
        if (g_card_open_descriptor != -1) {
            break;
        }
        i++;
    }
    return g_card_open_descriptor;
}
