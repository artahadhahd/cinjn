#include <texture.h>
#include <parsing/image.h>

struct texture {
    u32 id;
};

struct texture* create_2dtexture(const char* const path)
{
    i32 width, height, _channels;
    u8* data = stbi_load(path, &width, &height, &_channels, 0);
    if (data == NULL) {
        LOG("couldn't find texture", LOG_WARNING);
        LOG(path, LOG_WARNING);
        return NULL;
    }
    u32 id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);
    struct texture* texture = malloc(sizeof(struct texture));
    return texture;
}

void delete_texture(struct texture* this)
{
    if (this != NULL) {
        free(this);
        this = NULL;
    }
}