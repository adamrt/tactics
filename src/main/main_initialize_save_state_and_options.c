typedef unsigned char u8;
typedef unsigned int u32;

extern u8 a1, a2, a3, a4, a5, a6, a7, a8;
extern u32 options;
extern volatile u32 defaults;
extern u32 words[0x100], month, day;

void main_initialize_save_state_and_options(void) {
    int remaining = 0xff;
    u32* word = &words[0xff];
    u32 value;

    do {
        *word = 0;
        remaining--;
        word--;
    } while (remaining >= 0);

    value = 4;
    a2 = value;
    a5 = value;
    a6 = value;
    value = defaults;
    month = 1;
    day = 1;
    a1 = 14;
    a3 = 10;
    a4 = 32;
    a7 = 1;
    a8 = 0;
    options = value;
}
