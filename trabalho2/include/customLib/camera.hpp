#ifndef __camera__
#define __camera__

#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <map>
#include "customLib/userInput.hpp"

//Classe da camera utilizada no cenario
class camera{
private:
    float fov;          //angulo de fov da projection
    float aspect_ratio; //aspect-ratio da janela
    float near;         //Planos de corte em z-view
    float far;
    GLuint program;     //ID do Programa na GPU
    bool freeCamera;    //Ativa o modo free camera, andar pelo cenario livremente
    float speed;        //Velocidade na qual a camera anda pelo cenario
    float sensibility;
    float yaw;
    float pitch;

    void moveFront();
    void moveBack();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
public:
    glm::vec3 pos;      //Posicao da camera
    glm::vec3 front;    //Ponto para onde a camera esta olhando
    glm::vec3 up;       //Vetor viewUP

    camera(GLuint program, glm::vec3 pos, glm::vec3 front, glm::vec3 up, 
    float fov, float aspect_ratio, float near, float far, float speed, bool freeCamera);
    
    //move camera within scene
    void move(GLFWwindow* window);
    void direction(GLFWwindow* window);

    //Calcula as matrizes de view e projection e manda para a gpu
    void update();

    //Metodos Set
    void setFov(float fov);
    void setAspectRatio(float aspect_ratio);
    void setNear(float near);
    void setFar(float far);
    void setCameraMode(bool freeCamera);
    void setSpeed(float speed);
    void setSensibility(float sensibility);

    glm::vec3 getPos();
    ~camera();
};

#endif