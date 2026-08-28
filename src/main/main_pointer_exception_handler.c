extern int g_graphics_error;

extern void main_malloc_exception_handler(int zero, int error_code);

void main_pointer_exception_handler(int error_code) {
    main_malloc_exception_handler(0, error_code);
    g_graphics_error = 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
