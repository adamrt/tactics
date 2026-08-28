#ifndef FFT_PSX_GPU_H
#define FFT_PSX_GPU_H

#include "types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;

typedef struct {
    u32 tag;
    u32 code[15];
} DR_ENV;

typedef struct {
    RECT clip;
    s16 ofs[2];
    RECT tw;
    u16 tpage;
    u8 dtd;
    u8 dfe;
    u8 isbg;
    u8 r0;
    u8 g0;
    u8 b0;
    DR_ENV dr_env;
} DRAWENV;

typedef struct {
    RECT disp;
    RECT screen;
    u8 isinter;
    u8 isrgb24;
    u8 pad0;
    u8 pad1;
} DISPENV;

typedef struct {
    u32 mode;
    RECT* crect;
    u32* caddr;
    RECT* prect;
    u32* paddr;
} TIM_IMAGE;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
} POLY_F4;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad1;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad2;
} POLY_FT4;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    u8 r1;
    u8 g1;
    u8 b1;
    u8 pad1;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    u8 r2;
    u8 g2;
    u8 b2;
    u8 pad2;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad3;
    u8 r3;
    u8 g3;
    u8 b3;
    u8 pad4;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad5;
} POLY_GT4;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 w;
    s16 h;
} SPRT;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_MODE;

typedef char assert_rect_size[sizeof(RECT) == 8 ? 1 : -1];
typedef char assert_dr_env_size[sizeof(DR_ENV) == 64 ? 1 : -1];
typedef char assert_drawenv_size[sizeof(DRAWENV) == 92 ? 1 : -1];
typedef char assert_dispenv_size[sizeof(DISPENV) == 20 ? 1 : -1];
typedef char assert_tim_image_size[sizeof(TIM_IMAGE) == 20 ? 1 : -1];
typedef char assert_poly_f4_size[sizeof(POLY_F4) == 24 ? 1 : -1];
typedef char assert_poly_ft4_size[sizeof(POLY_FT4) == 40 ? 1 : -1];
typedef char assert_poly_gt4_size[sizeof(POLY_GT4) == 52 ? 1 : -1];
typedef char assert_sprt_size[sizeof(SPRT) == 20 ? 1 : -1];
typedef char assert_dr_mode_size[sizeof(DR_MODE) == 12 ? 1 : -1];

extern void FntLoad(int, int);
extern int FntOpen(int, int, int, int, int, int);
extern void FntFlush(int);
extern void SetDumpFnt(int);
extern int OpenTIM(void*);
extern int ReadTIM(TIM_IMAGE*);
extern void LoadTPage(u32*, int, int, int, int, int, int);
extern void LoadClut2(u32*, int, int);
extern void AddPrim(void*, void*);
extern void SetSemiTrans(void*, int);
extern void SetShadeTex(void*, int);
extern void SetPolyF3(void*);
extern void SetPolyFT3(void*);
extern void SetPolyG3(void*);
extern void SetPolyGT3(void*);
extern void SetPolyF4(POLY_F4*);
extern void SetPolyFT4(POLY_FT4*);
extern void SetPolyG4(void*);
extern void SetPolyGT4(void*);
extern void SetSprt8(void*);
extern void SetSprt16(void*);
extern void SetSprt(void*);
extern void SetTile1(void*);
extern void SetTile8(void*);
extern void SetTile16(void*);
extern void SetTile(void*);
extern void SetLineF2(void*);
extern void SetLineG2(void*);
extern void SetLineF3(void*);
extern void SetLineG3(void*);
extern void SetLineF4(void*);
extern void SetLineG4(void*);
extern void SetBlockFill(void*);
extern void SetDrawMove(void*);
extern int GetTPage(int, int, int, int);
extern int GetClut(int, int);
extern DR_MODE* SetDrawMode(DR_MODE*, int, int, int, RECT*);
extern void SetDispMask(int);
extern void ResetGraph(int);
extern void SetGraphDebug(int);
extern void DrawSyncCallback(void*);
extern int DrawSync(int);
extern void ClearImage(RECT*, u8, u8, u8);
extern void ClearOTag(void*, int);
extern s32 LoadImage(RECT*, u32*);
extern s32 StoreImage(RECT*, u32*);
extern s32 MoveImage(RECT*, s32, s32);
extern void DrawOTag(u32);
extern DRAWENV* SetDefDrawEnv(DRAWENV*, int, int, int, int);
extern DISPENV* SetDefDispEnv(DISPENV*, int, int, int, int);
extern DRAWENV* PutDrawEnv(DRAWENV*);
extern DISPENV* PutDispEnv(DISPENV*);

#endif
