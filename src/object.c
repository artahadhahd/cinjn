#include <object.h>

struct object new_object(void)
{
    u32 vao = 0, vbo = 0, ebo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    return (struct object) {
        NULL, // shader
        NULL, // texture
        NULL, // vertices
        NULL, // indices
        vao,
        vbo,
        ebo
    };
}

void attach_vertices(void* vertices, size_t vertex_length, size_t size, struct object* object)
{
    object->vertices = vertices;
    glGenBuffers(1, &object->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBufferData(GL_ARRAY_BUFFER, size * vertex_length, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}


static i32 ebo_len = 0;

void draw_object(struct object* self)
{
    if (self->vertices == NULL) return;
    use_shader(self->shader);
    glBindVertexArray(self->vao);
    if (self->indices != NULL) {
        glDrawElements(GL_TRIANGLES, ebo_len, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    } else if (self->vertices != NULL) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}

void attach_indices(void* indices, i32 length, size_t size, struct object* object)
{
    ebo_len = length;
    object->indices = indices;
    glGenBuffers(1, &object->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * size, indices, GL_STATIC_DRAW);
}

void attach_shader(struct shader* shader, struct object* this)
{
    this->shader = shader;
}

void draw_wireframe(struct object* this)
{
    if (this->vertices == NULL) return;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw_object(this);
    glBindVertexArray(this->vao);
    if (this->indices != NULL) {
        glDrawElements(GL_TRIANGLES, ebo_len, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    } else if (this->vertices != NULL) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}