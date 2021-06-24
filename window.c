#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "window.h"

GLFWwindow *init_window()
{
    if (!glfwInit())
    {
        printf("GLFW initialization failed!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cubes", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create window!\n");
        glfwTerminate();
        exit(1);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("GLEW error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        exit(1);
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);

    return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

float lastx = WINDOW_WIDTH/2.0, lasty = WINDOW_HEIGHT/2.0;
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos;
    lastx = xpos;
    lasty = ypos;

    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;
}

void process_input(GLFWwindow *window, struct Camera *camera, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // camera.pos += CAMERA_SPEED * camera.front
        glm_vec3_muladds(camera->front, CAMERA_SPEED * delta_time, camera->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm_vec3_muladds(camera->front, -CAMERA_SPEED * delta_time, camera->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        vec3 temp;
        glm_cross(camera->front, camera->up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, -CAMERA_SPEED * delta_time, camera->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        vec3 temp;
        glm_cross(camera->front, camera->up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, CAMERA_SPEED * delta_time, camera->pos);
    }

}