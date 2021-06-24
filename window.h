#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH    1280 
#define WINDOW_HEIGHT   720
#define SENSITIVITY     0.1f

GLFWwindow *init_window();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void process_input(GLFWwindow *window, struct Camera *camera, float delta_time);

#endif