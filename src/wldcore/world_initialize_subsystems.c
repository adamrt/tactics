#include "psx/types.h"

extern void SetDispMask(s32);
extern void func_80067E38(void);
extern void func_80068FA8(void);
extern void func_80068640(void);
extern void func_80067D70(void);
extern void func_8006AD28(void);
extern void func_8006A58C(void);
extern void func_8006C1FC(void);
extern void func_8008CB8C(void);
extern void func_8008D514(void);
extern void func_8008F284(void);
extern void func_8006C350(void);
extern void world_initialize_runtime_state(void);
extern void func_800683FC(void);

/* Initialize the WLDCORE subsystems before entering the world loop.
 * The matched range includes the jr delay slot at 0x80067cb0. */
void world_initialize_subsystems(void) {
    SetDispMask(0);
    func_80067E38();
    func_80068FA8();
    func_80068640();
    func_80067D70();
    func_8006AD28();
    func_8006A58C();
    func_8006C1FC();
    func_8008CB8C();
    func_8008D514();
    func_8008F284();
    func_8006C350();
    world_initialize_runtime_state();
    func_800683FC();
}
