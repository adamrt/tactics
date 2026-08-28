extern int g_weather_sfx_id;

extern void SuzukiPlaySound2(int sound_id);

void main_play_sound_2(int sound_id) {
    g_weather_sfx_id = sound_id;
    SuzukiPlaySound2(sound_id);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
