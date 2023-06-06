#ifndef __opengl_inits_ray__
#define __opengl_inits_ray__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#define W_HEIGHT 720
#define W_WIDTH 1280
#define FPS_LIMIT 60

GLFWwindow* init_window(void);

#endif