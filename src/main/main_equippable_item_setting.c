#include "psx/types.h"

void main_equippable_item_setting(u8* unit) {
    s32 support = unit[0x8F];

    if (support & 0x80) {
        unit[0x4C] |= 0x9;
    }
    if (support & 0x40) {
        unit[0x4C] |= 0x10;
    }
    if (support & 0x20) {
        unit[0x4A] |= 0x10;
    }
    if (support & 0x10) {
        unit[0x4A] |= 0x4;
    }
    if (support & 0x8) {
        unit[0x4B] |= 0x10;
    }
    if (support & 0x4) {
        unit[0x4B] |= 0x1;
    }
    if (support & 0x2) {
        unit[0x4A] |= 0x2;
    }
    if (support & 0x1) {
        unit[0x4B] |= 0x20;
    }
    support = unit[0x6];
    if (support & 0x40) {
        unit[0x4C] |= 0x42;
        unit[0x4D] |= 0x1;
    }
}
