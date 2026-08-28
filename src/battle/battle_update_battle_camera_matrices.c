#include "psx/gte.h"
#include "psx/libc.h"
#include "psx/types.h"

/* 32-byte rotation/translation matrix as libgte's MATRIX. */
typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} CameraMatrix;

extern void func_8001D658(void* src, void* dst);
extern void func_8001CF48(void* camera_matrix, void* offset_screen_coords);
extern void func_8001CF78(void* camera_matrix, void* scale);
extern void func_8001D0A8(void* camera_matrix);
extern void func_8001D138(void* camera_matrix);
extern void func_8001D578(void* integer_coords, void* source, void* result);

extern VECTOR D_800F5C2C;
extern u8 D_800F5C0C[8];
extern CameraMatrix D_800F6D94;
extern u8 D_800F5B9C[];
extern CameraMatrix D_800FBE60;
extern u8 D_800F5B34[];
extern u8 D_800FBDD4[];

void battle_update_battle_camera_matrices(CameraMatrix* camera_matrix, void* render_buffers,
    void* offset_screen_coords, VECTOR* camera_zoom) {
    u32 result;

    D_800F5C2C = *camera_zoom;
    memcpy(D_800F5C0C, render_buffers, 8);

    func_8001D658(render_buffers, camera_matrix);
    func_8001CF48(camera_matrix, offset_screen_coords);
    func_8001CF78(camera_matrix, &D_800F5C2C);
    func_8001D658(render_buffers, &D_800F6D94);
    func_8001D0A8(camera_matrix);
    func_8001D138(camera_matrix);
    func_8001D578(D_800F5B9C, D_800F6D94.t, &result);
    func_8001CF78(&D_800F6D94, &D_800F5C2C);

    *camera_matrix = D_800F6D94;
    D_800FBE60 = D_800F6D94;
    func_8001D658(D_800F5B34, D_800FBDD4);
}
