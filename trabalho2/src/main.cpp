#include "customLib/initsCG.hpp"
#include "customLib/camera.hpp"
#include "customLib/mesh.hpp"
#include "customLib/shaderClass.hpp"
#include "customLib/userInput.hpp"
#include "customLib/scenes/hut.hpp"
#include <iostream>

#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

/*
cd bin
mingw32-make
./main
*/


int main(void){
    GLFWwindow* window = init_window();

    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    shaderProgram.Activate();
    //Diz ao openGL para usar texturas com transparencia
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

    app user_control;

    //invisible cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    GLuint buffer[2];
    glGenBuffers(2, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

    //problmea com o mous AQUI
    hut_scene scene1(shaderProgram.ID, buffer);
    
    //set user controls
    glfwSetWindowUserPointer(window, &user_control);
    glfwSetKeyCallback(window, key_cb);
    glfwSetCursorPosCallback(window, cursor_cb);

    //showing window
    glfwShowWindow(window);
    //Inicializa o objeto de camera responsavel por criar as matrizes VIEW e PROJECTION do pipeline MVP
    camera camera(shaderProgram.ID/*program*/, glm::vec3 (1.0), glm::vec3 (1.0,  -4.0, -9.0), glm::vec3 (0.0, 1.0, 0.0), 45, ((float)W_WIDTH/(float)W_HEIGHT), 0.1f, 100.0f, 0.05, false);

    while (!glfwWindowShouldClose(window) && !user_control.key_state[GLFW_KEY_ESCAPE]) {   
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        //activate or not polygon mode
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        if(user_control.key_state[GLFW_KEY_P]){
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        camera.move(window);
        camera.direction(window);
        camera.update();               //atualiza e manda os valores das matrizes calculadas pelo objeto de camera para a GPU (VIEW e PROJECTION)

        
        //Posicionamento dos modelos no cenario e desenha cada objeto
        //scene1.scene_objects[2].translate(1.0, 0.0, 0.0);
        scene1.update(camera.pos, camera.front);

        glfwSwapBuffers(window);
    }

    // Delete all the objects we've created
	shaderProgram.Delete();

    glfwDestroyWindow(window);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

#ifdef _MSC_BUILD
#include "../lib/camera.cpp"
#include "../lib/initsCG.cpp"
#include "../lib/mesh.cpp"
#include "../lib/userInput.cpp"
#include "../lib/shaderClass.cpp"
#include "../lib/scenes/hut.cpp"
#include "glad.c"
#endif
