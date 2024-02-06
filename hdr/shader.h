#ifndef HDR_SHADER_H
#define HDR_SHADER_H
#include <types.h>
#include <utils/fs.h>
#include <utils/log.h>
#include <utils/resmgr.h>
#include <glad/glad.h>

#include <stdbool.h>

struct shader;

/**
 * @brief read a vertex shader and fragment shader and compile them to a shader program
 * @return `NULL` on failure
*/
struct shader* shader_from_file(const char* vertex_path, const char* fragment_path);
struct shader* shader_from_module(const char* name, struct resource_manager*);

/** @brief frees allocated memory and sets `shader` to NULL*/
void delete_shader(struct shader*);

void use_shader(const struct shader*);

void set_i32(const char* const name, const i32 value, const struct shader*);
void set_f32(const char* const name, const f32 value, const struct shader*);
#endif