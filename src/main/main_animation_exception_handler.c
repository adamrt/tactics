extern int g_graphics_error;

extern void main_do_nothing(int zero, int error_code);

void main_animation_exception_handler(int error_code) {
    main_do_nothing(0, error_code);
    g_graphics_error = 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
