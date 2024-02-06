#include <texture.h>
#include <parsing/image.h>

void delete_texture(struct texture* this)
{
    if (this->data != NULL) {
        free(this->data);
        this->data = NULL;
    }
    if (this != NULL) {
        free(this);
        this = NULL;
    }
}