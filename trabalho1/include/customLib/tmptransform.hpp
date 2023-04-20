#ifndef __tmp_transform__
#define __tmp_transform__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include "objects.hpp"

void translate(complex_object* obj, float new_x, float new_y);
void resize(complex_object* obj, float factor);

#endif