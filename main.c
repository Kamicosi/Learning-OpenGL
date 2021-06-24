#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/affine.h>
#include <cglm/cam.h>
#include <cglm/cglm.h>

#include <cglm/util.h>
#include <cglm/vec3.h>
#include <stdio.h>

#include "camera.h"
#include "cube.h"
#include "shader.h"
#include "texture.h"
#include "util.h"
#include "window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main(void)
{
    GLFWwindow *window = init_window();

    unsigned int program = create_program("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(program);

    struct Cube the_cube = create_cube("assets/miku.jpg");
    
    mat4 projection;
    float degrees = 45.0;
    glm_make_rad(&degrees);
    glm_perspective(degrees, ((float)WINDOW_WIDTH)/((float)WINDOW_HEIGHT), 0.1, 100.0, projection);

    vec3 cube_positions[] = {
        {0.0f, 0.0f, 0.0f},
        {2.0f, 5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        {2.4f, -0.4f, -3.5f},
        {-1.7f, 3.0f, -7.5f},
        {1.3f, -2.0f, -2.5f},
        {1.5f, 2.0f, -2.5f},
        {1.5f, 0.2f, -1.5f},
        {-1.3f, 1.0f, -1.5f}
    };

    struct Camera camera = {
        {0.0f, 0.0f, 3.0f},     // pos
        {0.0f, 0.0f, -1.0f},    // front
        {0.0f, 1.0f, 0.0f},     // up
        -90.0f,                 // yaw
        0.0f,                   // pitch
        0.0f                    // roll
    };

    float delta_time = 0.0f;
    float last_frame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        process_input(window, &camera, delta_time);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view;
        look_at(camera, view);

        shader_set_view(program, view);
        shader_set_projection(program, projection);

        for (int i = 0; i < 10; i++)
        {
            mat4 model = IDENTITY4;
            glm_translate(model, cube_positions[i]);
            float angle = 20.0f * i;
            glm_make_rad(&angle);
            glm_rotate(model, angle, (vec3){1.0f, 0.3f, 0.5f});
            shader_set_model(program, model);
            render_cube(the_cube);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete_cube(the_cube);
    glDeleteProgram(program);
    glfwTerminate();

    return 0;
}
