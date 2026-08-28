#include "psx/types.h"

extern u8 D_8013B8B8[];
extern void func_800F0520(u8* arg0);
extern void world_initialize_text_section_pointers(void);

void world_func_800f0574(void) {
    func_800F0520(D_8013B8B8);
    world_initialize_text_section_pointers();
}
