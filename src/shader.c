#include "shader.h"

struct shader {
    u32 id;
};

struct shader* shader_from_file(const char* vertex_path, const char* fragment_path)
{
    u8 ple = LOG_ERRORS;

    char* vertex_shader_source = read_file(vertex_path);
    if (vertex_shader_source == NULL) {
        LOG("Failed to read vertex shader", LOG_ERROR);
    }

    char* fragment_shader_source = read_file(fragment_path);
    if (fragment_shader_source == NULL) {
        LOG("Failed to read fragment shader", LOG_ERROR);
    }

    if (ple != LOG_ERRORS) {
        if (vertex_shader_source != NULL) {
            free(vertex_shader_source);
        }
        if (fragment_shader_source != NULL) {
            free(fragment_shader_source);
        }
        return NULL;
    }

    i32 success = 0;
    char shader_error[512];

    const u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, shader_error);
        LOG(shader_error, LOG_ERROR);
    }

    const u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, shader_error);
        LOG(shader_error, LOG_ERROR);
    }

    u32 program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, shader_error);
        LOG("Failed to link vertex with fragment shader", LOG_ERROR);
        LOG(shader_error, LOG_ERROR);
    }

    // clean up
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(vertex_shader_source);
    free(fragment_shader_source);

    if (LOG_ERRORS > 0) {
        return NULL;
    }

    struct shader* s = malloc(sizeof(struct shader));
    if (s != NULL) {
        s->id = program;
    }
    return s;
    // return (ple == LOG_ERRORS) ? s : NULL;
}

void use_shader(const struct shader* shader)
{
    if (shader != NULL) {
        glUseProgram(shader->id);
    }
}

void delete_shader(struct shader* shader)
{
    if (shader != NULL) {
        glDeleteProgram(shader->id);
        free(shader);
    }
    shader = NULL;
}

void set_i32(const char* const name, const i32 value, const struct shader* shader)
{
    glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void set_f32(const char* const name, const f32 value, const struct shader* shader)
{
    glUniform1f(glGetUniformLocation(shader->id, name), value);
}

struct shader* shader_from_module(const char* name, struct resource_manager* mgr)
{
    char* module_path = malloc(ALLOCATE_JOIN_PATH(mgr->cwd, name));
    join_path(module_path, mgr->cwd, name);
    if (!dir_exists(module_path)) {
        free(module_path);
        LOG("shader module not found:", LOG_WARNING);
        LOG(name, LOG_WARNING);
        return NULL;
    }
    const char* vertex_name = "vertex.glsl";
    const char* fragment_name = "fragment.glsl";

    // LOG(module_path, LOG_SIMPLE);
    char* vertex_path = malloc(ALLOCATE_JOIN_PATH(module_path, vertex_name));
    join_path(vertex_path, module_path, vertex_name);
    char* fragment_path = malloc(ALLOCATE_JOIN_PATH(module_path, fragment_name));
    join_path(fragment_path, module_path, fragment_name);

    struct shader* shader = shader_from_file(vertex_path, fragment_path);

    free(vertex_path);
    free(fragment_path);
    free(module_path);

    return shader;
}