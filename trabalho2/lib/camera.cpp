#include "customLib/camera.hpp"

//Construtor da camera
camera::camera(GLuint program, glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float aspect_ratio, float near, float far, float speed, bool freeCamera){
    this->program = program;
    this->pos = pos;
    this->front = front;
    this->up = up;
    this->fov = fov;
    this->aspect_ratio = aspect_ratio;
    this->near = near;
    this->far = far;
    this->freeCamera = freeCamera;
    this->speed = speed;
    this->sensibility = 0.1f;
    this->yaw =  -90.0;         
    this->pitch = 0.0;
}

//Movimentacao da camera para frente
void camera::moveFront(){
    if(this->freeCamera){
        this->pos += this->speed * this->front;
    }
    else{ //Nao eh uma free camera, logo y constante
        this->pos.x += this->speed * this->front.x;
        this->pos.z += this->speed * this->front.z;
    }
}

//Movimentacao da camera para tras
void camera::moveBack(){
    if(this->freeCamera){
        this->pos -= this->speed * this->front;
    }
    else{ //Nao eh uma free camera, logo y constante
        this->pos.x -= this->speed * this->front.x;
        this->pos.z -= this->speed * this->front.z;
    }
}

//Movimentacao da camera para esquerda
void camera::moveLeft(){
    if(this->freeCamera){
        this->pos -= glm::normalize(glm::cross(this->front, this->up)) * this->speed; 
    }
    else{
        this->pos.x -= glm::cross(this->front, this->up).x * this->speed;
        this->pos.z -= glm::cross(this->front, this->up).z * this->speed;
    }
}

//Movimentacao da camera para direita
void camera::moveRight(){
    if(this->freeCamera){
        this->pos += glm::normalize(glm::cross(this->front, this->up)) * this->speed; 
    }
    else{
        this->pos.x += glm::cross(this->front, this->up).x * this->speed;
        this->pos.z += glm::cross(this->front, this->up).z * this->speed;
    }
}

void camera::moveUp(){
    this->pos.y += this->speed;
}

void camera::moveDown(){
    this->pos.y -= this->speed;
}


void camera::move(GLFWwindow* window) {
    void* ptr = glfwGetWindowUserPointer(window);
    app* app_ptr = reinterpret_cast<app*>(ptr);

    if(app_ptr->key_state['W']) {
        this->moveFront();
    }
    if(app_ptr->key_state['A']) {
        this->moveLeft();
    }
    if(app_ptr->key_state['S']) {
        this->moveBack();
    }
    if(app_ptr->key_state['D']) {
        this->moveRight();
    }
    if(app_ptr->key_state[' ']) {
        this->moveUp();
    }
    if(app_ptr->key_state[GLFW_KEY_LEFT_SHIFT]) {
        this->moveDown();
    }
}

void camera::direction(GLFWwindow* window) {
    void* ptr = glfwGetWindowUserPointer(window);
    app* app_ptr = reinterpret_cast<app*>(ptr);

    yaw += (app_ptr->cursor.offset.x*sensibility);
    pitch += (app_ptr->cursor.offset.y*sensibility);
    
    if (pitch >= 89.0)
        pitch = 89.0;
    if (pitch <= -89.0)
        pitch = -89.0;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    //reset cursor offset, otherwise it will always have a delta movement
    app_ptr->cursor.offset.x = 0;
    app_ptr->cursor.offset.y = 0;
}

//Calcula os valores das matrizes de view e projection e manda para a gpu
void camera::update(){
    if(this->pos.x > 14.0f){ //Limites em x da camera no cenario
        this->pos.x = 14.0f;
    }
    else if(this->pos.x < -14.0f){
        this->pos.x = -14.0f;
    }

    if(this->pos.y > 14.0f){ //Limites em y da camera no cenario
        this->pos.y = 14.0f;
    }
    else if(this->pos.y < 0.1f){
        this->pos.y = 0.1f;
    }


    if(this->pos.z > 14.0f){  //Limites em z da camera no cenario
        this->pos.z = 14.0f;
    }
    else if(this->pos.z < -14.0f){
        this->pos.z = -14.0f;
    }
    
    
    //Calculo das matrizes de view e projection
    glm::mat4 m_view = glm::lookAt(this->pos, this->pos + this->front, this->up);
    glm::mat4 m_projection = glm::perspective(glm::radians(this->fov), this->aspect_ratio, this->near, this->far);


    //Manda para a gpu a matriz de view
    int loc_view = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(loc_view, 1, GL_FALSE, glm::value_ptr(m_view));

    //Manda para a gpu a matriz de projection
    int loc_projection = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(loc_projection, 1, GL_FALSE,glm::value_ptr(m_projection));    
}


//Sets methods
void camera::setFov(float fov){
    this->fov = fov;
}

void camera::setAspectRatio(float aspect_ratio){
    this->aspect_ratio = aspect_ratio;
}

void camera::setNear(float near){
    this->near = near;
}

void camera::setFar(float far){
    this->far = far;
}

void camera::setCameraMode(bool freeCamera){
    this->freeCamera = freeCamera;
}

void camera::setSpeed(float speed){
    this->speed = speed;
}

void camera::setSensibility(float sensibility){
    this->sensibility = sensibility;
}

camera::~camera(){}