#include "psx/types.h"

typedef struct EtcGraphic {
    const char* path;
    s32 lba;
    s32 size;
    void* framebuffer_rect;
    s16* dimensions;
    void* unused_14;
    void* unused_18;
    s32 texture_mode;
} EtcGraphic;

extern EtcGraphic g_etc_graphics[];
extern u8 g_etc_chapter_primitives_a[2][0xd0];
extern u8 g_etc_chapter_primitives_b[2][0xd0];
extern s32 g_event_speed;

extern void etc_build_chapter_graphic_polygons(
    s32 graphic_id, s32 fade, s32 blend_mode, s32 layer,
    void* primitives, s32 color);
extern void switch_to_next_thread(void);

void etc_show_chapter_title(s32 graphic_id) {
    /* The target reserves two otherwise unreferenced local words. */
    volatile s32 reserved_stack_words[2];
    s32 frame;
    s32 fade;
    s32 color;
    s16* dimensions;

    dimensions = g_etc_graphics[graphic_id].dimensions;
    frame = 0;
    fade = 0;
    if (dimensions[14] > 0) {
        do {
            etc_build_chapter_graphic_polygons(
                graphic_id, fade, 2, 0,
                g_etc_chapter_primitives_a[frame & 1], 0x80);
            etc_build_chapter_graphic_polygons(
                graphic_id, fade, 0, 1,
                g_etc_chapter_primitives_b[frame & 1], 0x80);
            frame++;
            switch_to_next_thread();
            fade += g_event_speed;
        } while (fade < dimensions[14]);
    }

    fade = 0;
    do {
        etc_build_chapter_graphic_polygons(
            graphic_id, dimensions[14], 2, 0,
            g_etc_chapter_primitives_a[frame & 1], 0x80);
        etc_build_chapter_graphic_polygons(
            graphic_id, dimensions[14], 0, 1,
            g_etc_chapter_primitives_b[frame & 1], 0x80);
        frame++;
        switch_to_next_thread();
        fade += g_event_speed;
    } while (fade < 0x50);

    color = 0x80;
    fade = 0;
    do {
        etc_build_chapter_graphic_polygons(
            graphic_id, dimensions[14], 2, 0,
            g_etc_chapter_primitives_a[frame & 1], color);
        etc_build_chapter_graphic_polygons(
            graphic_id, dimensions[14], 0, 1,
            g_etc_chapter_primitives_b[frame & 1], color);
        color -= g_event_speed;
        switch_to_next_thread();
        fade += g_event_speed;
        frame++;
    } while (fade < 0x80);
}
