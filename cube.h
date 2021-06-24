#ifndef CUBE_H
#define CUBE_H

struct Cube {
    unsigned int vao;
    unsigned int vbo;
    unsigned int texture;
};

struct Cube create_cube(const char *tex_path);
void render_cube(struct Cube cube);
void delete_cube(struct Cube cube);

#endif