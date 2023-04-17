#ifndef __opengl_objects__
#define __opengl_objects__

#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

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
        coordinates *vertices;

        base_object(int _nvertices, int _position_on_vector);
        void delete_object(void);
        void draw_object(GLint loc, GLint loc_color, GLuint program, float mat_transform[16], float R, float G, float B, float opaccity);
};


vertices_accumulator* vectorize_objects(std::vector<base_object> objects);

#endif