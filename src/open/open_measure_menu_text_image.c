#include "psx/types.h"

typedef struct OpenTextImageDimensions {
    s32 width;
    s32 height;
} OpenTextImageDimensions;

u8* world_find_text_entry(s32 combined_text_index);
void world_measure_text(s16* columns, s16* rows, u8* text);

void open_measure_menu_text_image(s32 combined_text_index,
    OpenTextImageDimensions* dimensions) {
    s16 columns;
    s16 rows;
    u8* text;

    text = world_find_text_entry(combined_text_index);
    world_measure_text(&columns, &rows, text);
    dimensions->width = ((columns * 10) + 24) & 0xfffc;
    dimensions->height = (rows << 4) + 16;
}
