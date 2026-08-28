extern int g_current_tune;
extern int main_set_current_music_target(int volume, int time);

int main_play_tune(int tune) {
    if (tune != 0) {
        int* current_tune = &g_current_tune;

        if (*current_tune == 0) {
            main_set_current_music_target(0, 120);
            *current_tune = tune | 0x80;
        }
    }
    return 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
