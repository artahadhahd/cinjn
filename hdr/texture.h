#ifndef HDR_TEXTURE_H
#define HDR_TEXTURE_H
#include <types.h>
#include <stdlib.h>
#include <utils/log.h>
#include <glad/glad.h>

struct texture;

struct texture* create_2dtexture(const char* const path);
void delete_texture(struct texture*);
#endif