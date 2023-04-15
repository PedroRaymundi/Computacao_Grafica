#include "customLib/objects.hpp"

base_object::base_object(int _nvertices) : nvertices(_nvertices){
    vertices = (coordinates*) malloc(sizeof(coordinates)*nvertices);
    position_on_vector = -1;
}

void base_object::delete_object(void) {
    free(vertices);
}

void base_object::draw_object(GLint loc, GLint loc_color, GLuint program, float mat_rotation[16], int B) {
    loc = glGetUniformLocation(program, "mat_transformation");
    glUniformMatrix4fv(loc, 1, GL_TRUE, mat_rotation);

        //hexagono
    glDrawArrays(GL_TRIANGLE_FAN, position_on_vector, (sizeof(coordinates)*nvertices));
                            // R, G, B, opac
    glUniform4f(loc_color, 1, 0, B, 1.0);
}

objects_handler* vectorize_objects(base_object* objects, int nobjects) {
    objects_handler *ohandler = (objects_handler*) malloc(sizeof(objects_handler));
    int k = 0;

    ohandler->nvertices = 0;

    for (int i = 0; i < nobjects; i++) {
        ohandler->nvertices += objects[i].nvertices;
    }

    ohandler->all_objects = (coordinates*) malloc(sizeof(coordinates)*ohandler->nvertices);
    
    for (int i = 0; i < nobjects; i++) {
        for (int j = 0; j < objects[i].nvertices; j++) {
            ohandler->all_objects[k] = objects[i].vertices[j];
            k++;
        }
    }

    return ohandler;
}