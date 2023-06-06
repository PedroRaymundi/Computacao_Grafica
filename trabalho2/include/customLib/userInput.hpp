#ifndef __user_input_glfw__
#define __user_input_glfw__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <map>
#include "initsCG.hpp"

typedef struct _mouse_coord_ {
    float x;
    float y;
} mouse_coord;

typedef struct _mouse_ {
    mouse_coord last = {/*.x = */ (float)W_HEIGHT/(float)2, /*.y = */ (float)W_WIDTH/(float)2};
    mouse_coord offset;
    void change_state(float xpos, float ypos);
} mouse;

typedef struct _app_ {
    std::map<int, int> key_state;
    mouse cursor;
    void change_state(int key, int action);
} app;

void cursor_cb(GLFWwindow* window, double xpos, double ypos);
void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif