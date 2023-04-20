#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "customLib/initsRay.hpp"
#include "customLib/objects.hpp"
#include "customLib/actors.hpp"
#include "customLib/app.hpp"
#include <cmath>
#include <iostream>
#include <vector>

/*
cd bin
mingw32-make
./main
*/

#define _PI 3.1415926535
#define _PI_2 (_PI / 2.0)

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
    space_ship.inclination = M_PI/2;
    //Transladar e rotacionar
    space_ship.t.set_translation(Vector3(0.5, -0.6, 0.0));
    space_ship.t.set_scale(Vector3(0.3));

    meteor space_meteor(index_end_obj_vec);
    index_end_obj_vec = space_meteor.end_position_on_vector;
    all_objects.push_back(space_meteor);
    //Transladar e redimensionar 
    space_meteor.t.set_translation(Vector3(-0.2, 0.4, 0.0));
    space_meteor.t.set_scale(Vector3(0.7));

    star shooting_star(index_end_obj_vec);
    index_end_obj_vec = shooting_star.end_position_on_vector;
    all_objects.push_back(shooting_star);
    //Transladar e rotacionar 
    shooting_star.t.set_translation(Vector3(-0.6, -0.5, 0.0));
    shooting_star.t.set_scale(Vector3(0.2));

    float alien_x, alien_y;
    alien hiding_alien(index_end_obj_vec);
    index_end_obj_vec = hiding_alien.end_position_on_vector;
    all_objects.push_back(hiding_alien);
    //Transladar e rotacionar 
    alien_y = 0.0;
    alien_x = 0.0;
    hiding_alien.t.set_translation(Vector3(alien_x, alien_y, 0.0));
    hiding_alien.t.set_scale(Vector3(0.5));

    planet planet_mars(index_end_obj_vec);
    index_end_obj_vec = planet_mars.end_position_on_vector;
    all_objects.push_back(planet_mars);
    //Transladar e redimensionar 
    planet_mars.t.set_translation(Vector3(0, 0, 0.0));
    planet_mars.t.set_scale(Vector3(1.1));

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

    const double fpsLimit = 1.0 / 60.0;
    double lastUpdateTime = 0;  // number of seconds since the last loop
    double lastFrameTime = 0;   // number of seconds since the last frame

    const float MOV_SPEED = 0.05;
    float vel = 0.01;

    // Initial angle the comet will be at
    float orbit_theta = 0.0f;
    const float orbit_r = 0.7;
    while (!glfwWindowShouldClose(window)) {

        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;

        glfwPollEvents();

        // This if-statement only executes once every 60th of a second
        if ((now - lastFrameTime) >= fpsLimit){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 0.0);

            orbit_theta += MOV_SPEED;
//            if (orbit_theta >= 2 * _PI) orbit_theta -= 2 * _PI;

            Vector3 comet_pos(orbit_r * cos(orbit_theta),
                              orbit_r * sin(orbit_theta),
                              0.0f);

            space_meteor.t.identity();
            space_meteor.t.scale(0.7);
            space_meteor.t.rotate(_PI_2 + orbit_theta, Vector3(0.0, 0.0, 1.0));
            space_meteor.t.set_translation(comet_pos);

            if(alien_y >= 0.5)
                vel = -MOV_SPEED;
            else if (alien_y <= 0.0)
                vel = +MOV_SPEED;

            alien_y += vel;

            space_ship.move(key_input.key_state);
            hiding_alien.t.set_translation(Vector3(alien_x, alien_y, 0.0f));
        
            space_meteor.draw_object(loc, loc_color, program);
            hiding_alien.draw_object(loc, loc_color, program);
            planet_mars.draw_object(loc, loc_color, program);
            shooting_star.draw_object(loc, loc_color, program);
            space_ship.draw_object(loc, loc_color, program);
        
            glfwSwapBuffers(window);

            // only set lastFrameTime when you actually draw something
            lastFrameTime = now;
        }

        // set lastUpdateTime every iteration
        lastUpdateTime = now;

    }
 
    space_ship.delete_object();
    space_meteor.delete_object();
    planet_mars.delete_object();
    hiding_alien.delete_object();
    shooting_star.delete_object();

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
#include "../lib/app.cpp"
#include "glad.c"
#endif
