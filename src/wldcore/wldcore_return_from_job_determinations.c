#include "psx/types.h"

extern void func_80069934(u8* dst, u8 value);
extern s32 func_8007920C(s32 job_id);
extern void func_80079844(void);
extern void func_80079C6C(void);
extern void func_80079E14(void);
extern void func_8007A148(void);

extern u8 D_80057EED[];
extern u8 D_8009F2EC[];
extern s32 D_8009F1F8;
extern s32 D_8009F1EC;

void wldcore_return_from_job_determinations(s32 job_id) {
    u8* entry = &D_80057EED[job_id * 9];

    func_80069934(D_8009F2EC, *entry);
    D_8009F1F8 = job_id;
    D_8009F1EC = func_8007920C(job_id);
    func_80079844();
    func_80079C6C();
    func_80079E14();
    func_8007A148();
}
