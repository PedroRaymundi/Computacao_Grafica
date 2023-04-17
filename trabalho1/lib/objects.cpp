#include "customLib/objects.hpp"

base_object::base_object(int _nvertices, int _position_on_vector) : nvertices(_nvertices), position_on_vector(_position_on_vector){
    vertices = (coordinates*) malloc(sizeof(coordinates)*nvertices);
}

void base_object::delete_object(void) {
    free(vertices);
}

void base_object::draw_object(GLint loc, GLint loc_color, GLuint program, float mat_transform[16], float R, float G, float B, float opaccity) {
    loc = glGetUniformLocation(program, "mat_transformation");
    glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transform);
    //método, início (n entendi), número de coordenadas
    glDrawArrays(GL_TRIANGLE_FAN, position_on_vector, nvertices);
    glUniform4f(loc_color, R, G, B, opaccity);
}

vertices_accumulator* vectorize_objects(std::vector<base_object> objects) {
    vertices_accumulator *ohandler = (vertices_accumulator*) malloc(sizeof(vertices_accumulator));
    int nobjects = objects.size();
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