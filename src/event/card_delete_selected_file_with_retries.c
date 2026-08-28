#include "psx/types.h"

extern u8 g_card_selected_slot;
extern const char g_card_slot_0_path[];
extern const char g_card_slot_1_path[];

extern char* strcpy(char* destination, const char* source);
extern char* strcat(char* destination, const char* source);
extern s32 card_wait_for_operation_result(s32 retry_limit);
extern s32 FileDelete(const char* path);

s32 card_delete_selected_file_with_retries(const char* filename) {
    char path[256];
    /* The retail O0 frame reserves one word between the path and result. */
    s32 path_padding;
    s32 result;
    s32 i;

    if (g_card_selected_slot == 0) {
        strcpy(path, g_card_slot_0_path);
    } else {
        strcpy(path, g_card_slot_1_path);
    }
    strcat(path, filename);

    for (i = 0; i < 10; i++) {
        if (card_wait_for_operation_result(10) != 0) {
            return 0;
        }
        result = FileDelete(path);
        if (result != 0) {
            return result;
        }
    }
    return 0;
}
