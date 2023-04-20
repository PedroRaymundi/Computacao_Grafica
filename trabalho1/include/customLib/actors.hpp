#ifndef __project_actors__
#define __project_actors__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "objects.hpp"
#include <iostream>
#include <vector>
#include <cmath>

class ship : public complex_object {
    public:
        float speed;
        float inclination;

        ship(int _start_position_on_vector);
        void move();
};

class meteor : public complex_object {
    public:
        meteor(int _start_position_on_vector);
};

class planet : public complex_object {
    public:
        planet(int _start_position_on_vetor);
};

class star : public complex_object {
    public:
        star(int _start_position_on_vetor);
};

class alien : public complex_object {
    public:
        alien(int _start_position_on_vetor);
};

#endif