#include "customLib/initsRay.hpp"

class base_shader {
    public:
        // GLSL para Fragment Shader
        const char* fragment_code =
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";

        // GLSL para Vertex Shader
        const char* twod_vertex_code =
        "attribute vec2 position;\n"
        "uniform mat4 mat_transformation;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mat_transformation * vec4(position,0.0,1.0);\n"
        "}\n";
        

        // GLSL para Vertex Shader
        const char* threed_vertex_code =
        "attribute vec3 position;\n"
        "uniform mat4 mat_transformation;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mat_transformation * vec4(position, 1.0);\n"
        "}\n";
};

GLFWwindow* init_window(void) {
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela

    //Modo tela cheia (esta distorcido por enqnt)
    //GLFWwindow* window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "Minha Janela",  glfwGetPrimaryMonitor(), NULL);

     GLFWwindow* window = glfwCreateWindow(1000,1000, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    return window;
}

/// @param two_dimensional if working with two dimensional applications, set this to true
GLuint init_shaders(bool two_dimensional) {
    base_shader shader;

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    if (two_dimensional) {
        glShaderSource(vertex, 1, &shader.twod_vertex_code, NULL);
    } else {
        glShaderSource(vertex, 1, &shader.threed_vertex_code, NULL);
    }
    glShaderSource(fragment, 1, &shader.fragment_code, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char *info = (char*) malloc(sizeof(char)*infoLength);
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",info);
        free(info);
    }

    

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char *info = (char*) malloc(sizeof(char)*infoLength);
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",info);
        free(info);
    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);

    return program;
}

