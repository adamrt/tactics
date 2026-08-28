#include "psx/types.h"

/* Disc sectors and byte budgets of the resident sound files (LBAs from the
 * disc inventory: WAVESET.WD 85007, SYSTEM.SED 85002, ENV.SED 85000). */
#define WAVESET_WD_SECTOR 0x14C0F
#define WAVESET_WD_SIZE   0x79000
#define SYSTEM_SED_SECTOR 0x14C0A
#define SYSTEM_SED_SIZE   0x2800
#define ENV_SED_SECTOR    0x14C08
#define ENV_SED_SIZE      0x1000

/* Sector/size pairs of MUSIC_45.SMD .. MUSIC_49.SMD (LBA 85378..85382), the
 * five short tunes that stay loaded for the whole session. */
typedef struct PermanentSmdFile {
    s32 sector;
    s32 size;
} PermanentSmdFile;

#define PERMANENT_SMD_COUNT 5

extern u32 g_low_overlay_load_address;
extern u8 g_system_sed_data[];
extern u8 g_env_sed_data[];
extern s32 g_forced_music[];
extern s32 g_current_tune;
extern s32 g_music_handles;
extern s32 g_weather_sfx_id;
extern s32 g_permanent_smd_data[PERMANENT_SMD_COUNT];
extern PermanentSmdFile g_permanent_smd_files[PERMANENT_SMD_COUNT];

extern void SuzukiSPUInitialiser(s32 arg0);
extern void main_clear_smd_allocator_table(void);
extern s32 main_get_wd(s32 sector, s32 size, void* dest);
extern void put_waveset_wd_in_spu(s32 arg0);
extern void SuzukiAppendVFXSMD(s32 arg0);
extern s32 main_get_smd(s32 sector, s32 size);

void main_scus_opengnrcsfx(void) {
    s32 i;

    SuzukiSPUInitialiser(0);
    main_clear_smd_allocator_table();
    put_waveset_wd_in_spu(main_get_wd(WAVESET_WD_SECTOR, WAVESET_WD_SIZE,
        (void*)g_low_overlay_load_address));
    SuzukiAppendVFXSMD(main_get_wd(SYSTEM_SED_SECTOR, SYSTEM_SED_SIZE, g_system_sed_data));
    SuzukiAppendVFXSMD(main_get_wd(ENV_SED_SECTOR, ENV_SED_SIZE, g_env_sed_data));

    /* Clears the music-state words 0x8004d964 (g_forced_music) and, via the
     * same base, the seven slot words after g_music_handles
     * (0x8004d974..0x8004d98c); the original indexes them from this base. */
    g_forced_music[0] = 0;
    g_current_tune = 0;
    g_music_handles = 0;
    for (i = 6; i >= 0; i--) {
        g_forced_music[i + 4] = 0;
    }

    g_weather_sfx_id = 0;
    g_permanent_smd_data[0] = main_get_smd(g_permanent_smd_files[0].sector,
        g_permanent_smd_files[0].size);
    g_permanent_smd_data[1] = main_get_smd(g_permanent_smd_files[1].sector,
        g_permanent_smd_files[1].size);
    g_permanent_smd_data[2] = main_get_smd(g_permanent_smd_files[2].sector,
        g_permanent_smd_files[2].size);
    g_permanent_smd_data[3] = main_get_smd(g_permanent_smd_files[3].sector,
        g_permanent_smd_files[3].size);
    g_permanent_smd_data[4] = main_get_smd(g_permanent_smd_files[4].sector,
        g_permanent_smd_files[4].size);
}
