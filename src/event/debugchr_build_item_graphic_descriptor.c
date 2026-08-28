#include "psx/gpu.h"
#include "psx/types.h"

typedef struct DebugchrItemGraphicData {
    u8 unknown_00[0xc];
    u8 x_load_location;
    u8 y_load_location;
    u16 clut;
    u8 unknown_10[8];
} DebugchrItemGraphicData;

typedef struct DebugchrGraphicDescriptor {
    s16 x_load_location;
    s16 y_load_location;
    s16 width;
    s16 height;
    u16 clut;
    s16 tpage;
} DebugchrGraphicDescriptor;

extern void get_item_graphic_data(DebugchrItemGraphicData* output, u32 item_id);

void debugchr_build_item_graphic_descriptor(DebugchrGraphicDescriptor* output,
    u32 item_id) {
    DebugchrItemGraphicData graphic;

    get_item_graphic_data(&graphic, item_id);
    output->x_load_location = graphic.x_load_location;
    output->y_load_location = graphic.y_load_location;
    output->width = 16;
    output->height = 16;
    output->clut = graphic.clut;
    output->tpage = GetTPage(0, 0, 0x380, 0x120);
}
