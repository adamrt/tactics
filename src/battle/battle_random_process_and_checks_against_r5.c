#include "psx/types.h"

extern s32 battle_random_process_gives_a_number_between_0_7fff(void);

s32 battle_random_process_and_checks_against_r5(s32 arg0, s32 arg1) {
    return (s32)(battle_random_process_gives_a_number_between_0_7fff() * arg0) / 32768 >= arg1;
}
