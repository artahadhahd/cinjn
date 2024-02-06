// https://tchayen.github.io/posts/ttf-file-parsing
#include <parsing/ttf.h>

static const char get_u8(struct TTF_File* file) {
    return file->data[file->position++];
}

static const char get_u16(struct TTF_File* file) {
    return (get_u8(file) << 8) | get_u8(file);
}