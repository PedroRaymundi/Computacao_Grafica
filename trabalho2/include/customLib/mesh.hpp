#ifndef __mesh__
#define __mesh__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <math.h>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <string>

void loadCubemap(std::vector<std::string> faces);

//Enum que indica em que eixo deve ser realizada a rotacao
typedef enum{
    X, Y, Z
}direction;

//Struct de informacoes a respeito das texturas
typedef struct{
    std::string texture_path;       //Caminho diretorio de arquivos
    GLenum format;                  //Formato: RGB ou RGBA
}texture_info;

//Classe responsavel por inicializar os vertices de cada modelo, aplicar transfs geometricas sob estes e mandar sua respectiva matriz model a gpu
class mesh{
    protected:
        int n_vertices; //numero de vertices que o objeto tem
        int firstVertice_index; //index do primeiro vertice do objeto no vetor de vertices do cenario
        std::string filePath;   //filePath do .obj do objeto
        GLuint program;         //Id do programa na gpu
        std::vector<int> texture_groups; //Quantos vertices tem cada grupo de textura do objeto
        std::vector<GLuint> texture_id;  //Vetor de id de textura de cada grupo de textura
    public:
        mesh(GLuint program, std::string filePath, std::vector<texture_info> texturePath ,std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec3 > & out_normals, std::vector < glm::vec2 > & out_uvs, bool cubeMap = false, bool wolf = false);
        
        //Transformacoes geometricas que podem ser aplicadas ao objeto
        void translate(float tx, float ty, float tz);
        void rotate(float angle, direction d);
        void scale(float sx, float sy, float sz);
        
        //Matriz de model do objeto-> cada objeto tem sua propria matriz model segundo o pipeline MVP
        glm::mat4 m_model;

        //Manda a matriz de model para a gpu e desenha o objeto
        void update();
};

class CubemapMesh {
    protected:
        int n_vertices; //numero de vertices que o objeto tem
        int firstVertice_index; //index do primeiro vertice do objeto no vetor de vertices do cenario
        std::string filePath;   //filePath do .obj do objeto
        glm::mat4 m_model;      //Matriz de model do objeto-> cada objeto tem sua propria matriz model segundo o pipeline MVP
        GLuint program;         //Id do programa na gpu
        std::vector<int> texture_groups; //Quantos vertices tem cada grupo de textura do objeto
        std::vector<GLuint> texture_id;  //Vetor de id de textura de cada grupo de textura
    public:
        CubemapMesh(GLuint program, std::string filePath, std::vector<texture_info> texturePath ,std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec3 > & out_normals, std::vector < glm::vec2 > & out_uvs);
};

#endif