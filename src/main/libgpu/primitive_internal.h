#ifndef FFT_LIBGPU_PRIMITIVE_INTERNAL_H
#define FFT_LIBGPU_PRIMITIVE_INTERNAL_H

#include "psx/types.h"

#define DEFINE_PRIMITIVE_SETTER(name, words, command) \
    void name(void* primitive) {                      \
        u8* bytes = (u8*)primitive;                   \
        bytes[3] = (words);                           \
        bytes[7] = (command);                         \
    }

#define DEFINE_LINE_SETTER(name, words, command, pad_offset) \
    void name(void* primitive) {                             \
        u8* bytes = (u8*)primitive;                          \
        bytes[3] = (words);                                  \
        bytes[7] = (command);                                \
        *(u32*)(bytes + (pad_offset)) = 0x55555555;          \
    }

#endif
