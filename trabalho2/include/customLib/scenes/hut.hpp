#ifndef __hut_scene__
#define __hut_scene__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "customLib/mesh.hpp"
#include "customLib/userInput.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include "customLib/wolf.hpp"
#include "customLib/knife.hpp"

class hut_scene {
    public:
        hut_scene(GLuint program, GLuint* buffer);
        void update(glm::vec3 pos, glm::vec3 projection, app user_control);
        std::vector<mesh> scene_objects;
    
    private:
        GLuint program;
        GLuint* buffer;

        std::vector< glm::vec3 > v_vertices;  //Vetor de coordenadas de vertices do cenario
        std::vector< glm::vec2 > v_uvs;       //Vetor de coordenadas de textura do cenario 
        std::vector< glm::vec3 > v_normals;   //Vetor de normais do cenario
		
		glm::mat4 wolf_logic(glm::vec3 pos, size_t w, bool started);
		
		size_t wolf_start;
		std::vector <Wolf> wolves;
		Knife wolf_killer_knife;
};

#endif