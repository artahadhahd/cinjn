#ifndef HDR_TEXTURE_H
#define HDR_TEXTURE_H
#include <types.h>
#include <stdlib.h>
#include <utils/log.h>
#include <glad/glad.h>

struct texture {
    i32 width, height, channels;
    u8* data;
    size_t data_length;
};

struct texture* create_2dtexture_from_file(const char* const path);
void delete_texture(struct texture*);
#endif