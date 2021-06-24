#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

unsigned int create_program(char *vertex_path, char *fragment_path)
{
    char *vertex_source = read_from_file(vertex_path);
    char *fragment_source = read_from_file(fragment_path);
    if (vertex_source && fragment_source)
    {

        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, (const char * const *)&vertex_source, NULL);
        glCompileShader(vertex_shader);
        int success;
        char info_log[512];
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
            printf("Vertex shader error: %s\n", info_log);
            exit(1);
        }

        unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, (const char * const *)&fragment_source, NULL);
        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
            printf("Fragment shader error: %s\n", info_log);
            exit(1);
        }

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, NULL, info_log);
            printf("Linking error: %s", info_log);
            exit(1);
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        free(vertex_source);
        free(fragment_source);

        return program;
    }
    else
    {
        return 0;
    }
}

char *read_from_file(char *path)
{
    char *result = NULL;
    int len;
    FILE *file = fopen(path, "r");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fseek(file, 0, SEEK_SET);
        result = calloc(len+1, sizeof(char));
        if (result)
        {
            fread(result, 1, len, file);

        }
        fclose(file);
    }
    return result;
}

void shader_set_model(unsigned int program, mat4 model)
{
    int model_loc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float *)model);
}

void shader_set_view(unsigned int program, mat4 view)
{
    int view_loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)view);
}

void shader_set_projection(unsigned int program, mat4 projection)
{
    int proj_loc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (float *)projection);
}