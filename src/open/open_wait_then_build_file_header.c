#include "psx/types.h"

extern void open_wait_for_pending_file(void);
extern void main_build_file_header_nnl(
    void* header,
    s32 sector,
    s32 sector_count,
    void* destination);

void open_wait_then_build_file_header(
    void* header,
    s32 sector,
    s32 sector_count,
    void* destination) {
    open_wait_for_pending_file();
    main_build_file_header_nnl(header, sector, sector_count, destination);
}
