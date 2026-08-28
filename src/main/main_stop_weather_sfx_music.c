extern int g_weather_sfx_id;

extern void SuzukiTurnOffAllMusic(void);

void main_stop_weather_sfx_music(void) {
    g_weather_sfx_id = 0;
    SuzukiTurnOffAllMusic();
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
