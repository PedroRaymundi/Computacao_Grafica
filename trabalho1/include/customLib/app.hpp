#ifndef __app_glfw__
#define __app_glfw__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <map>

typedef struct _app_ {
    std::map<int, int> key_state;
    void change_state(int key, int action);
} app;

void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif