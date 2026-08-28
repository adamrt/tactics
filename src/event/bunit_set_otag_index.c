#include "psx/types.h"

extern s16 g_bunit_otag_index;

/* Select the ordering-table bucket used by subsequent menu packets. */
void bunit_set_otag_index(s16 value) {
    g_bunit_otag_index = value;
}
