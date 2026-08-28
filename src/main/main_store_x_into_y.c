typedef unsigned char u8;

void main_store_x_into_y(u8* src, u8* dst, int count) {
    int i;

    for (i = 0; i < count; i++) {
        *dst++ = *src++;
    }
}
