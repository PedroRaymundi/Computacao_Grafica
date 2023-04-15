#ifndef __opengl_inits_ray__
#define __opengl_inits_ray__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

GLFWwindow* init_window(void);
GLuint init_shaders(bool two_dimensional = false);

#endif