extern int g_file_still_loading;

int main_check_file_still_loading(void) {
    return g_file_still_loading;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
