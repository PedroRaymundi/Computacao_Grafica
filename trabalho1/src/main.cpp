#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "customLib/initsRay.hpp"
#include "customLib/objects.hpp"
#include "customLib/actors.hpp"
#include "customLib/app.hpp"
#include "customLib/tmptransform.hpp"
#include <cmath>
#include <iostream>
#include <vector>

/*
cd bin
mingw32-make
./main
*/


int main(void){
    app key_input;

    GLFWwindow* window = init_window();
    GLuint program = init_shaders(true);

    // Preparando dados para enviar a GP
    std::vector<complex_object> all_objects;
    int index_end_obj_vec = 0;

    ship space_ship(index_end_obj_vec);
    index_end_obj_vec = space_ship.end_position_on_vector;
    all_objects.push_back(space_ship);

    meteor space_meteor(index_end_obj_vec);
    index_end_obj_vec = space_meteor.end_position_on_vector;
    all_objects.push_back(space_meteor);

    planet planet_mars(index_end_obj_vec);
    index_end_obj_vec = planet_mars.end_position_on_vector;
    all_objects.push_back(planet_mars);
    translate(&planet_mars, 0.2, -0.2);
    resize(&planet_mars, 0.5);

    vertices_accumulator* vaccumulator = vectorize_objects(all_objects);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    
    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates)*vaccumulator->nvertices, vaccumulator->all_objects, GL_DYNAMIC_DRAW);


    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vaccumulator->all_objects[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
 
    // Associando variávels do programa GLSL (Fragment Shader) para definir cores
    GLint loc_color = glGetUniformLocation(program, "color");

    //associando eventos de teclas
    glfwSetWindowUserPointer(window, &key_input);
    glfwSetKeyCallback(window, key_cb);

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        
        space_ship.draw_object(loc, loc_color, program);
        space_meteor.draw_object(loc, loc_color, program);
        planet_mars.draw_object(loc, loc_color, program);
        
        glfwSwapBuffers(window);
        
    }
 
    space_ship.delete_object();
    space_meteor.delete_object();
    planet_mars.delete_object();
    free(vaccumulator->all_objects);
    free(vaccumulator);

    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

// TODO: unity build because we are chads
#ifdef _MSC_BUILD
#include "../lib/initsRay.cpp"
#include "../lib/objects.cpp"
#include "../lib/actors.cpp"
#include "glad.c"
#endif

