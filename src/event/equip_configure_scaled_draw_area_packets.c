#include "psx/types.h"

extern s32 g_event_speed;
extern const u16 g_equip_draw_area_scale_percent[12];
extern void world_copy_bytes(void* destination, const void* source, s32 count);
extern void SetDrawArea(void* packet, const void* rectangle);

void equip_configure_scaled_draw_area_packets(u8* packet, const void* source,
    s32 scale_index, s32 lower_half,
    const s16* offset) {
    s32 scale;
    s32 width;
    s32 height;
    u32 width_bits;
    u32 height_bits;
    s32 scaled_width;
    register s32 scaled_height __asm__("$12");
    s32 final_width_product;
    s32 width_reduction;
    s32 height_reduction_base;

    if (g_event_speed == 2) {
        scale_index *= 2;
    }
    if (scale_index >= 12) {
        scale_index = 11;
    }
    scale = g_equip_draw_area_scale_percent[scale_index];
    world_copy_bytes(packet + 0x18, source, 8);

    width_bits = *(u16*)(packet + 0x1c);
    width = (s32)(width_bits << 16) >> 16;
    scaled_width = width * scale;
    width_reduction = scaled_width / 200;
    height_bits = *(u16*)(packet + 0x1e);
    height = (s32)(height_bits << 16) >> 16;
    scaled_height = height * scale;
    height_reduction_base = scaled_height / 200 + (scaled_height >> 31);
    scaled_height >>= 31;
    *(s16*)(packet + 0x18) -= 0x80;
    *(s16*)(packet + 0x18) += offset[0];
    *(s16*)(packet + 0x1a) += offset[2];
    *(s16*)(packet + 0x18) = width / 2 + *(s16*)(packet + 0x18) - width_reduction;
    width_reduction = height_reduction_base - scaled_height;
    *(s16*)(packet + 0x1a) = height / 2 + *(s16*)(packet + 0x1a) - width_reduction;
    final_width_product = (*(s16*)(packet + 0x1c)) * scale;
    *(s16*)(packet + 0x1c) = final_width_product / 100;
    *(s16*)(packet + 0x1e) = (*(s16*)(packet + 0x1e) * scale) / 100;
    if (lower_half != 0) {
        *(s16*)(packet + 0x22) = 0;
    } else {
        *(s16*)(packet + 0x22) = 0xf0;
        *(s16*)(packet + 0x1a) += 0xf0;
    }
    SetDrawArea(packet, packet + 0x18);
    SetDrawArea(packet + 0xc, packet + 0x20);
}
