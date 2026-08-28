#include "psx/types.h"

extern void switch_to_next_thread(void);
extern void battle_stop_current_thread(void);
extern s32 g_companion_executable_request_index;
extern s32 D_80166008;
extern u16 D_80173C80;

void battle_setup_open_companion_executable(s32 arg0) {
    while (g_companion_executable_request_index != 0 || D_80166008 != 0) {
        switch_to_next_thread();
    }
    g_companion_executable_request_index = arg0;
    if (arg0 != 0) {
        do {
            switch_to_next_thread();
        } while (g_companion_executable_request_index != 0);
    }
    if (D_80173C80 == 1) {
        battle_stop_current_thread();
    }
}
