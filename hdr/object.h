#ifndef HDR_OBJECT_H
#define HDR_OBJECT_H
#include <types.h>
#include <shader.h>
#include <texture.h>

/** @brief use this function with attach_indices and attach_vertices */
#define UNPACK_METADATA(p) p, sizeof(p), sizeof(p[0])

struct object {
    struct shader* shader;
    void* textures;
    void* vertices;
    void* indices;
    u32 vao, vbo, ebo, texture;
};

struct object new_object(void);
void draw_object(struct object*);
void draw_wireframe(struct object*);
void attach_vertices(void* vertices, size_t vertex_length, size_t size, struct object*);
void attach_indices(void* indices, i32 length, size_t size, struct object*);
void attach_shader(struct shader*, struct object*);
// void delete_object(struct objects*);
#endif