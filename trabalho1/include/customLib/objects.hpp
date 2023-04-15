#ifndef __opengl_objects__
#define __opengl_objects__

#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

typedef struct __coordinates__{
    float x, y;
} coordinates;

typedef struct __objects_handler__ {
    int nvertices;
    coordinates* all_objects;
} objects_handler;


class base_object {  
    public:
        int nvertices;
        int position_on_vector;
        coordinates *vertices;

        base_object(int _nvertices);
        void delete_object(void);
        void draw_object(GLint loc, GLint loc_color, GLuint program, float mat_rotation[16], int B);
};

objects_handler* vectorize_objects(base_object* objects, int nobjects);

#endif