#include <customLib/scenes/hut.hpp>


hut_scene::hut_scene (GLuint program, GLuint* buffer) {
    this->program = program;
    this->buffer = buffer;

    std::vector<texture_info> textures; //Vetor auxiliar de informacoes de texturas usadas na malha
    
    //Criacao do modelo da malha de cabana com suas respectivas texturas
    textures.push_back({"../obj/cabana/WoodCabinDif.jpg",GL_RGB});
    textures.push_back({"../obj/cabana/WoodCabinDif.jpg",GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/cabana/cabana.obj", textures, v_vertices, v_normals, v_uvs, false));
    textures.clear();

    //Criacao do modelo da malha do terreno externo de areia com sua respectiva textura
    textures.push_back({"../obj/terreno/areia.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/terreno/terreno.obj", textures, v_vertices, v_normals, v_uvs, false));
    textures.clear();

    textures.push_back({"../obj/skybox/dark_horizon.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/skybox/sky.obj", textures, v_vertices, v_normals, v_uvs, false));
    textures.clear();


    //Envia o vetor de coordenadas dos vertices do cenario para a GPU
    glBufferData(GL_ARRAY_BUFFER, v_vertices.size() * sizeof(glm::vec3), &v_vertices[0], GL_STATIC_DRAW);
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    
    //Envia o vetor de coordenadas de textura do cenario para a GPU
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, v_uvs.size() * sizeof(glm::vec2), &v_uvs[0], GL_STATIC_DRAW);
    GLint loc_texture_coord = glGetAttribLocation(program, "texture_coord");
    glEnableVertexAttribArray(loc_texture_coord);
    glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);

    //positioning, rotating and scaling objects
    //hut
    scene_objects[0].scale(0.1f,0.1f,0.1f);
    //terrain
    scene_objects[1].scale(15.0f,15.0f,15.0f);
    //skybox
    scene_objects[2].scale(15.0f, 15.0f, 15.0f);
}

void hut_scene::update(glm::vec3 pos, glm::vec3 projection) {
    //atualização da skybox para manter o player sempre ao centro dela
    //TODO atualizar a textura horrível que eu fiz pra skybox
    scene_objects[2].m_model = glm::translate(glm::mat4(1.0f), pos);
    scene_objects[2].scale(50.0f, 50.0f, 50.0f);
    for(int i = 0; i < scene_objects.size(); i++) {
        scene_objects[i].update();
    }
}