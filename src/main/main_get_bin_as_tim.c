extern void* get_tim(int sector, int size);
extern void main_animation_exception_handler(int error_code);

void* main_get_bin_as_tim(int sector, int size) {
    void* result = get_tim(sector, size);

    if (result == 0) {
        main_animation_exception_handler(2);
    }
    return result;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
