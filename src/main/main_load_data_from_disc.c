typedef unsigned char u8;

extern int build(void*, int, int, void*, int);
extern void poll(void*);
extern int vsync(int);
extern u8 fd;
extern int busy;

void main_load_data_from_disc(int sector, int sectors, void* destination,
    int suppress_loading_display) {
    u8* descriptor = &fd;

    build(descriptor, sector, sectors, destination, suppress_loading_display);
    while (busy != 0) {
        poll(descriptor);
        vsync(0);
    }
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
