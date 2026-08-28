extern void main_game_free(void* pointer);

void main_call_game_free(void* pointer) {
    main_game_free(pointer);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
