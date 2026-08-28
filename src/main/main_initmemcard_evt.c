#include "psx/etc.h"
#include "psx/types.h"

extern u8 g_card_bios_events_opened;
/* Eight memory-card BIOS event handles: SwCARD then HwCARD, each with IOE,
 * ERROR, TIMOUT and NEW.  Element 0 is what event/ and open/ poll as
 * g_card_bios_event_done. */
extern s32 g_card_bios_events[];

extern void EnterCriticalSection(void);
extern s32 OpenEvent(s32 desc, s32 spec, s32 mode, s32 func);
extern void init_card_earlysafe(s32 val);
extern void StartCARD_earlysafe(void);
extern void ChangeClearPad(s32 val);
extern void _bu_init(void);
extern void _card_auto(s32 val);
extern void EnableEvent(s32 event);
extern void ExitCriticalSection(void);

void main_initmemcard_evt(void) {
    s32 i;

    if (g_card_bios_events_opened != 0) {
        return;
    }
    i = 0;
    EnterCriticalSection();
    g_card_bios_events[0] = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, 0);
    g_card_bios_events[1] = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, 0);
    g_card_bios_events[2] = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, 0);
    g_card_bios_events[3] = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, 0);
    g_card_bios_events[4] = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, 0);
    g_card_bios_events[5] = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, 0);
    g_card_bios_events[6] = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, 0);
    g_card_bios_events[7] = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, 0);
    init_card_earlysafe(1);
    StartCARD_earlysafe();
    ChangeClearPad(0);
    _bu_init();
    _card_auto(0);
    for (i = 0; i < 8; i++) {
        EnableEvent(g_card_bios_events[i]);
    }
    ExitCriticalSection();
    g_card_bios_events_opened = 1;
}
