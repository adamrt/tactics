extern int g_music_handles[];

int main_get_music_handle(int slot) {
    return g_music_handles[slot];
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
