extern int g_weather_sfx_id;

extern void accumulate_channels_to_pause(int sound_id);

void main_stop_playing_sfx(int sound_id) {
    if (sound_id == g_weather_sfx_id) {
        g_weather_sfx_id = 0;
    }
    accumulate_channels_to_pause(sound_id);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
