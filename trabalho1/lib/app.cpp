#include "customLib/app.hpp"

void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // get pointer
    void* ptr = glfwGetWindowUserPointer(window);
    // cast
    app* app_ptr = reinterpret_cast<app*>(ptr);
    // call func
    app_ptr->change_state(key, action);
}

void app::change_state(int key, int action) {
    key_state[key] = action;
    //std::cout << "tecla: " << key << " action: " << action << "\n";
}