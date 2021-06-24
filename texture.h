#ifndef TEXTURE_H
#define TEXTURE_H

enum Image_Type
{
    INVALID,
    PNG,
    JPG
};

unsigned int init_texture(const char *path);
enum Image_Type check_valid_file(const char *path);

#endif