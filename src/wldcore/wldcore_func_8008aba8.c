#include "psx/types.h"

typedef struct {
    u8 data[0x38];
} D80059594Entry;

extern D80059594Entry D_80059594[];
extern s16 D_800BB4FC;
extern void func_8008ABE4(D80059594Entry* entry);

void wldcore_func_8008aba8(void) {
    func_8008ABE4(&D_80059594[D_800BB4FC]);
}
