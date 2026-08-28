extern int g_current_scenario_music;

int main_get_current_scenario_music(void) {
    return g_current_scenario_music;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
