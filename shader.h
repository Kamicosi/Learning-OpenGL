#ifndef SHADER_H
#define SHADER_H

#include <cglm/cglm.h>

unsigned int create_program(char *vertex_path, char *fragment_path);
char *read_from_file(char *path);
void shader_set_model(unsigned int program, mat4 model);
void shader_set_view(unsigned int program, mat4 view);
void shader_set_projection(unsigned int program, mat4 projection);

#endif