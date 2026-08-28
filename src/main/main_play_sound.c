extern void SuzukiPlaySound1(int sound_id);

void main_play_sound(int sound_id) {
    SuzukiPlaySound1(sound_id);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
