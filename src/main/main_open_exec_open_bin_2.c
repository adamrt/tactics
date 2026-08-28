extern void* g_low_overlay_load_address;

extern void* main_get_dat_as_wd(int sector, int size, void* destination);
extern void open_bin_entrypoint_2(void);

void main_open_exec_open_bin_2(void) {
    main_get_dat_as_wd(0x14ff0, 0x36800, g_low_overlay_load_address);
    open_bin_entrypoint_2();
}
