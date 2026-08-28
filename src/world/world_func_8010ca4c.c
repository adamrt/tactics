#include "fft/data.h"

extern s16 D_8018AAEA;
extern party_data_t* main_get_party_data_pointer(s32 index);

/* Assembles party_data_t.name_id from its two bytes (the target uses lbu/lbu,
 * not lhu, so the halfword field is not read directly). */
s32 world_func_8010ca4c(void) {
    u8* name_id = (u8*)&main_get_party_data_pointer(D_8018AAEA)->name_id;

    return (name_id[1] << 8) | name_id[0];
}
