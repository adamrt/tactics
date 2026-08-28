#include "psx/types.h"

extern u8 g_file_header[];

extern void main_build_file_header_nnl(void* header, int sector, int sectors, void* destination);

void main_call_build_file_header(int sector, int size, void* destination) {
    main_build_file_header_nnl(g_file_header, sector, (u32)size >> 11, destination);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
