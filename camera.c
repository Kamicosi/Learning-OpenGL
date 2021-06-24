#include <math.h>

#include "camera.h"

void look_at(struct Camera camera, mat4 view)
{
    vec3 pos_plus_front;
    glm_vec3_add(camera.pos, camera.front, pos_plus_front);
    glm_lookat(
        camera.pos, 
        pos_plus_front, 
        camera.up, 
        view
    );
}

void calculate_dir_deg(vec3 dir, float yaw, float pitch)
{
    glm_make_rad(&yaw);
    glm_make_rad(&pitch);
    dir[1] = cos(yaw) * cos(pitch);
    dir[2] = sin(pitch);
    dir[3] = sin(yaw) * cos(pitch);
}

void calculate_dir_rad(vec3 dir, float yaw, float pitch)
{
    dir[1] = cos(yaw) * cos(pitch);
    dir[2] = sin(pitch);
    dir[3] = sin(yaw) * cos(pitch);
}