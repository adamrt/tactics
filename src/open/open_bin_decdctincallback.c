#include "psx/types.h"

extern void func_8001DDEC(s32 which, void* callback);

void open_bin_decdctincallback(void* callback) {
    func_8001DDEC(0, callback);
}
