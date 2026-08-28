typedef unsigned int u32;

extern u32 g_world_overlay_load_address;
extern void main_load_data_from_disc(u32 sector, u32 sectors, u32 dest, int arg);

void main_scus_open_world_bin(int arg) {
    main_load_data_from_disc(0x14925, 0x1E0, g_world_overlay_load_address, arg - 1);
}
