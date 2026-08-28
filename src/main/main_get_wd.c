typedef unsigned char u8;

extern int load(void*, int, int, void*);
extern int vsync(int);
extern void tick(void);
extern void poll(void*);
extern u8 fd;
extern int busy;

void* main_get_wd(int sector, unsigned int size, void* d) {
    void* destination = d;
    /* Pinned: unpinned (local or inline &fd), descriptor and destination
     * swap $s0/$s1. */
    register u8* descriptor __asm__("$16") = &fd;

    while (load(descriptor, sector, size >> 11, destination) != 0) {
        vsync(0);
        tick();
        poll(descriptor);
    }
    while (busy != 0) {
        vsync(0);
        tick();
        poll(descriptor);
    }
    return destination;
}
