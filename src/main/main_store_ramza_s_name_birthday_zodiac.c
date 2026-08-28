#include "psx/types.h"

extern u8* main_get_party_data_pointer(s32 slot);
extern void main_copy_byte_data(const u8* source, u8* destination, s32 count);

void main_store_ramza_s_name_birthday_zodiac(u8* save) {
    s32 slot;
    u8* unit;
    u16* packed;
    u8* name;
    u32 birthday;

    if (save[0] >= 4) {
        return;
    }
    for (slot = 0; slot < 20; slot++) {
        unit = main_get_party_data_pointer(slot);
        if (unit[1] == 0xff) {
            continue;
        }
        if (unit[0] >= 4) {
            continue;
        }
        name = save + 0x12c;
        packed = (u16*)(save + 8);
        birthday = (unit[5] + (unit[6] << 8)) & 0x1ff;
        *packed = (*packed & 0xfe00) | birthday;
        *packed = (*packed & 0xfff) | ((unit[6] >> 4) << 12);
        main_copy_byte_data(unit + 0xbe, name, 0x10);
        return;
    }
}
