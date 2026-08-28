#ifndef FFT_PSX_ETC_H
#define FFT_PSX_ETC_H

extern int VSync(int);
extern void ResetCallback(void);
extern void VSyncCallback(void*);
extern void PadInit(int);

/* Psy-Q kernel.h event descriptors (DescHW|0x11, DescSW|0x01), event specs
 * and event modes, as passed to OpenEvent by the memory-card setup. */
#define HwCARD     0xF0000011
#define SwCARD     0xF4000001
#define EvSpIOE    0x0004
#define EvSpTIMOUT 0x0100
#define EvSpNEW    0x2000
#define EvSpERROR  0x8000
#define EvMdNOINTR 0x2000

#endif
