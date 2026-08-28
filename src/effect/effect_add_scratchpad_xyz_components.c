typedef unsigned short u16;

typedef struct EffectWideVector {
    u16 x;
    u16 pad_x;
    u16 y;
    u16 pad_y;
    u16 z;
} EffectWideVector;

void effect_add_scratchpad_xyz_components(
    int group,
    int point,
    const EffectWideVector* offset,
    u16* output) {
    int point_offset = point * 3;
    int group_offset = group * 51;
    int element = group_offset + point_offset;
    u16* scratchpad = (u16*)0x1f800000;

    output[0] = scratchpad[element] + offset->x;
    output[1] = scratchpad[element + 1] + offset->y;
    output[2] = scratchpad[element + 2] + offset->z;
}
