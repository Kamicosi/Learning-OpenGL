#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "texture.h"
#include "stb_image.h"

unsigned int init_texture(const char *path)
{
    enum Image_Type image_type = check_valid_file(path);
    if (image_type == INVALID)
    {
        printf("Not a valid image file: %s", path);
        exit(1);
    }
    unsigned int texture;
    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data)
    {
        printf("Failed to load texture\n");
        exit(1);
    }
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (image_type == PNG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else if (image_type == JPG)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return texture;
}

enum Image_Type check_valid_file(const char *path)
{
    char *dot = strchr(path, '.');
    if (strcmp(dot, ".png") == 0)
    {
        return PNG;
    }
    else if (strcmp(dot, ".jpg") == 0)
    {
        return JPG;
    }
    else 
    {
        return INVALID;
    }
}