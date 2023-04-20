#include "customLib/objects.hpp"

base_object::base_object(int _nvertices, int _position_on_vector) : nvertices(_nvertices), position_on_vector(_position_on_vector) {

    vertices = (coordinates*) malloc(sizeof(coordinates)*nvertices);
    opaccity = 1.0;
}

void base_object::delete_object(void) {
    free(vertices);
}

//---------complex object----------

complex_object::complex_object() {}

void complex_object::draw_object(GLint loc, GLint loc_color, GLuint program) {
    int totelements = object_element.size();

    for (int i = 0; i < totelements; i++) {
        loc = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, t.vals);
        glUniform4f(loc_color, object_element[i].R, object_element[i].G, object_element[i].B, object_element[i].opaccity);
        //método, primeira posição no vetor geral de vértices, número de vértices
        glDrawArrays(GL_TRIANGLE_FAN, object_element[i].position_on_vector, object_element[i].nvertices);
    }
}

void complex_object::delete_object(void) {
    int totelements = object_element.size();

    for (int i = 0; i < totelements; i++) {
        free(object_element[i].vertices);
    }
}

vertices_accumulator* vectorize_objects(std::vector<complex_object> objects) {
    vertices_accumulator *ohandler = (vertices_accumulator*) malloc(sizeof(vertices_accumulator));
    int nobjects = objects.size();
    int l = 0;

    ohandler->nvertices = 0;

    for (int i = 0; i < nobjects; i++) {
        for (int j = 0; j < objects[i].object_element.size(); j++) {
            ohandler->nvertices += objects[i].object_element[j].nvertices;
        }
    }

    ohandler->all_objects = (coordinates*) malloc(sizeof(coordinates)*ohandler->nvertices);
    
    for (int i = 0; i < nobjects; i++) {
        for (int j = 0; j < objects[i].object_element.size(); j++) {
            for (int k = 0; k < objects[i].object_element[j].nvertices; k++) {
                ohandler->all_objects[l] = objects[i].object_element[j].vertices[k];
                l++;
            }
        }
    }

    return ohandler;
}