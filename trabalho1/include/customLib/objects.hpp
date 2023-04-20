#ifndef __opengl_objects__
#define __opengl_objects__

#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <customLib/transform.hpp>

typedef struct __coordinates__{
    float x, y;
} coordinates;

typedef struct __vertices_accumulator__ {
    int nvertices;
    coordinates* all_objects;
} vertices_accumulator;


class base_object {  
    public:
        int nvertices;
        int position_on_vector;
        float R, G, B, opaccity;
        coordinates *vertices;

        base_object(int _nvertices, int _position_on_vector);
        void delete_object(void);
};

class complex_object {
    public:
        int start_position_on_vector;
        int end_position_on_vector;
        Transform t;
        std::vector<base_object> object_element; 
        
        complex_object();
        void draw_object(GLint loc, GLint loc_color, GLuint program);
        void delete_object(void);
};

vertices_accumulator* vectorize_objects(std::vector<complex_object> objects);

#endif