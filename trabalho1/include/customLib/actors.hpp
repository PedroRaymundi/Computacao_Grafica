#ifndef __project_actors__
#define __project_actors__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "objects.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

class ship : public complex_object {
    public:
        float speed;
        float inclination;
        float x, y;

        ship(int _start_position_on_vector);
        void move(std::map<int, int> key_state);
};

class meteor : public complex_object {
    public:
        bool collided;
        meteor(int _start_position_on_vector);
};

class planet : public complex_object {
    public:
        planet(int _start_position_on_vetor);
};

class star : public complex_object {
    public:
        float growth;

        star(int _start_position_on_vetor);
        void grow(std::map<int, int> key_state);
};

class alien : public complex_object {
    public:
        bool collided;
        alien(int _start_position_on_vetor);
};

class explosion : public complex_object {
    public:
        explosion(int _start_position_on_vetor);
};

#endif