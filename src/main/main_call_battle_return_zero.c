extern int g_battle_overlay_loaded;
extern int battle_return_zero(void);

int main_call_battle_return_zero(void) {
    if (g_battle_overlay_loaded == 0) {
        return 0;
    }
    return battle_return_zero();
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
