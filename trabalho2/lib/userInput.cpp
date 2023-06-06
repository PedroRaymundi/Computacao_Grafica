#include "customLib/userInput.hpp"

void mouse::change_state(float xpos, float ypos) {
    //calculate cursor delta movement
    offset.x = xpos - last.x;
    offset.y = last.y - ypos;
    
    //save last mouse position
    last.x = xpos;
    last.y = ypos;
}   

void app::change_state(int key, int action) {
    key_state[key] = action;
    //std::cout << "tecla: " << key << " action: " << action << "\n";
}

void cursor_cb(GLFWwindow* window, double xpos, double ypos) {
    // get pointer
    void* ptr = glfwGetWindowUserPointer(window);
    // cast
    app* app_ptr = reinterpret_cast<app*>(ptr);
    // call func
    app_ptr->cursor.change_state(xpos, ypos);
}

void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // get pointer
    void* ptr = glfwGetWindowUserPointer(window);
    // cast
    app* app_ptr = reinterpret_cast<app*>(ptr);
    // call func
    app_ptr->change_state(key, action);
}