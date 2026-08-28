#include "psx/gpu.h"
#include "psx/types.h"

typedef struct RequireItemGraphicData {
    u8 unknown_00[0xc];
    u8 x_load_location;
    u8 y_load_location;
    u16 clut;
    u8 unknown_10[8];
} RequireItemGraphicData;

typedef struct RequireGraphicDescriptor {
    s16 x_load_location;
    s16 y_load_location;
    s16 width;
    s16 height;
    u16 clut;
    s16 tpage;
} RequireGraphicDescriptor;

extern void get_item_graphic_data(RequireItemGraphicData* output, u32 item_id);

void require_build_item_graphic_descriptor(RequireGraphicDescriptor* output,
    u32 item_id) {
    RequireItemGraphicData graphic;

    get_item_graphic_data(&graphic, item_id);
    output->x_load_location = graphic.x_load_location;
    output->y_load_location = graphic.y_load_location;
    output->width = 16;
    output->height = 16;
    output->clut = graphic.clut;
    output->tpage = GetTPage(0, 0, 0x380, 0x120);
}
