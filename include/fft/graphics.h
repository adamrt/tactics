#ifndef FFT_GRAPHICS_H
#define FFT_GRAPHICS_H

typedef enum texture_uv_flip {
    TEXTURE_UV_FLIP_NONE = 0,
    TEXTURE_UV_FLIP_X = 1,
    TEXTURE_UV_FLIP_Y = 2,
    TEXTURE_UV_FLIP_XY = TEXTURE_UV_FLIP_X | TEXTURE_UV_FLIP_Y,
} texture_uv_flip_t;

#endif
