extern void* main_get_wd(int sector, unsigned int size, void* destination);
extern void main_animation_exception_handler(int error_code);

void* main_get_dat_as_wd(int sector, int size, void* destination) {
    void* result = main_get_wd(sector, size, destination);

    if (result == 0) {
        main_animation_exception_handler(2);
    }
    return result;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
