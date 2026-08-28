#include "psx/types.h"

typedef struct CardDirectoryEntry {
    u8 name[20];
    u32 attributes;
    s32 size;
    u8 remainder[12];
} CardDirectoryEntry;

extern u8 g_card_selected_slot;
extern const char g_card_slot_0_path[];
extern const char g_card_slot_1_path[];
extern const char g_card_save_file_pattern[];
extern const char g_card_all_file_pattern[];

extern char* strcpy(char* destination, const char* source);
extern char* strcat(char* destination, const char* source);
extern CardDirectoryEntry* firstfile(char* pattern, CardDirectoryEntry* entry);
extern CardDirectoryEntry* nextfile(CardDirectoryEntry* entry);

s32 card_enumerate_save_files(CardDirectoryEntry* entries, s32 all_files) {
    s32 count;
    char path[128];

    if (g_card_selected_slot == 0) {
        strcpy(path, g_card_slot_0_path);
    } else {
        strcpy(path, g_card_slot_1_path);
    }
    if (all_files == 0) {
        strcat(path, g_card_save_file_pattern);
    } else {
        strcat(path, g_card_all_file_pattern);
    }

    count = 0;
    if (firstfile(path, entries) == entries) {
        do {
            count++;
            entries++;
        } while (nextfile(entries) == entries);
    }
    return count;
}
