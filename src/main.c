#include <stdio.h>
#include <glad/glad.h>
#include <glfw3/glfw3.h>
#include <utils/log.h>
#include <shader.h>
#include <string.h>
#include <stdlib.h>
#include <object.h>
#include <texture.h>
#include <utils/resmgr.h>
// #include <crtdbg.h>

static f32 vertices[12] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

u32 indices[] = {
    0, 1, 3,
    1, 2, 3,
    0, 3, 1
};



int main() {
    if (!glfwInit()) {        LOG("Failed to initialize glfw", LOG_ERROR);        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* win = glfwCreateWindow(800, 900, "cafebabe", NULL, NULL);

    if (!win) {
        glfwTerminate();
        LOG("Failed to create window", LOG_ERROR);
        return 1;
    }

    glfwMakeContextCurrent(win);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG("FAiled to initialize GLAD", LOG_ERROR);
        glfwTerminate();
        return 1;
    }

    struct resource_manager* shader_manager = create_resource_manager();
    if (find_dir(JOIN_PATH("res", "shader"), DefaultSearchDepth, shader_manager)) {
        LOG("Failed to load resource manager", LOG_WARNING);
    }

    struct shader* s = shader_from_module("triangle", shader_manager);
    struct texture* texture = create_2dtexture_from_file("../res/wall.jpg");

    struct object o = new_object();
    attach_indices(UNPACK_METADATA(indices), &o);
    attach_vertices(UNPACK_METADATA(vertices), &o);
    attach_shader(s, &o);

    while (!glfwWindowShouldClose(win)) {
        glClearColor(1.0f, 0.0f, 1.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        draw_object(&o);
        glfwSwapBuffers(win);
        glfwPollEvents();
        if (LOG_ERRORS > 0) break;
    }
    glfwTerminate();

    delete_shader(s);
    delete_resource_manager(shader_manager);
    delete_texture(texture);

    // _CrtDumpMemoryLeaks();
    return LOG_ERRORS;
}