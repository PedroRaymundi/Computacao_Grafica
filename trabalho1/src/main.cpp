#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "customLib/initsRay.hpp"
#include "customLib/objects.hpp"
#include <cmath>
#include <iostream>
#include <vector>

/*
cd bin
mingw32-make
./main
*/

int main(void){

    GLFWwindow* window = init_window();
    GLuint program = init_shaders(true);

    // Preparando dados para enviar a GP
    std::vector<base_object> total_objects;
    base_object sq1(4, 0);
    sq1.vertices[0] = { -0.5f, +0.5f }; 
    sq1.vertices[1] = { +0.5f, +0.5f };
    sq1.vertices[2] = { +0.5f, -0.5f };
    sq1.vertices[3] = { -0.5f, -0.5f };
    total_objects.push_back(sq1);

    base_object sq2(4, sq1.nvertices);
    sq2.vertices[0] = { -0.35f, +0.35f }; 
    sq2.vertices[1] = { +0.35f, +0.35f };
    sq2.vertices[2] = { +0.35f, -0.35f };
    sq2.vertices[3] = { -0.35f, -0.35f };
    total_objects.push_back(sq2);

    base_object sq3(4, sq1.nvertices+sq2.nvertices);
    sq3.vertices[0] = { -0.25f, +0.25f }; 
    sq3.vertices[1] = { +0.25f, +0.25f };
    sq3.vertices[2] = { +0.25f, -0.25f };
    sq3.vertices[3] = { -0.25f, -0.25f };
    total_objects.push_back(sq3);

    base_object sq4(4, sq1.nvertices+sq2.nvertices+sq3.nvertices);
    sq4.vertices[0] = { -0.05f, +0.05f }; 
    sq4.vertices[1] = { +0.05f, +0.05f };
    sq4.vertices[2] = { +0.05f, -0.05f };
    sq4.vertices[3] = { -0.05f, -0.05f };
    total_objects.push_back(sq4);

    vertices_accumulator* vaccumulator = vectorize_objects(total_objects);

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

    // Exibindo nossa janela
    glfwShowWindow(window);

    float angulo = 0.0f;
    float angulo_inc = 0.5f;

    float c = 1.0f; // armazenar cosseno (da matriz de rotacao)
    float s = 0.0f; // armazenar seno  (da matriz de rotcao)

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        
        angulo += angulo_inc;
        c = cos( ((angulo) * M_PI / 180.0) ); // cos considerando conversao para radianos
        s = sin( ((angulo) * M_PI / 180.0) );

        float mat_rotation[16] = {
            1, 0, 0.0f, 0.0f,
            0, 1, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        //A COR TA INDO EM ORDEM, MAS COMEÇA PELO ÚLTIMO (?????????????????????)
        sq1.draw_object(loc, loc_color, program, mat_rotation, 0, 0, 1, 1.0f);
        sq2.draw_object(loc, loc_color, program, mat_rotation, 0, 1, 0, 1.0f);
        sq3.draw_object(loc, loc_color, program, mat_rotation, 1, 0, 0, 1.0f);
        sq4.draw_object(loc, loc_color, program, mat_rotation, 1, 1, 1, 1.0f);
        
        glfwSwapBuffers(window);
        
    }
 
    sq1.delete_object();
    sq2.delete_object();
    sq3.delete_object();
    sq4.delete_object();
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
#include "glad.c"
#endif

