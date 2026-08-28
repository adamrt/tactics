#include "psx/types.h"

extern s32 g_etc_graphics[][8];

extern s32 battle_get_first_thread_parameter(void);
extern void etc_open_graphic(s32 graphic_id);
extern void etc_show_chapter_title(s32 graphic_id);
extern void etc_show_game_over(s32 graphic_id);
extern void stop_current_event_thread(void);

void etc_show_graphic_async(void) {
    s32 graphic_id;
    s32 graphic_type;

    graphic_id = battle_get_first_thread_parameter();
    etc_open_graphic(graphic_id);
    graphic_type = g_etc_graphics[graphic_id][7];
    if (graphic_type == 0) {
        etc_show_chapter_title(graphic_id);
    } else if (graphic_type == 1) {
        etc_show_game_over(graphic_id);
    }
    stop_current_event_thread();
}
