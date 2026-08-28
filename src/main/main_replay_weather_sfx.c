extern int g_weather_sfx_id;

extern void SuzukiPlaySound2(int sound_id);

void main_replay_weather_sfx(void) {
    int sound_id = g_weather_sfx_id;

    if (sound_id != 0) {
        SuzukiPlaySound2(sound_id);
    }
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
