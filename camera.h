#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

#define CAMERA_SPEED    3.0f

struct Camera {
    vec3 pos;
    vec3 front;
    vec3 up;

    float yaw;
    float pitch;
    float roll;
};

void look_at(struct Camera camera, mat4 view);
void calculate_dir_deg(vec3 dir, float yaw, float pitch);
void calculate_dir_rad(float *dir, float yaw, float pitch);

#endif