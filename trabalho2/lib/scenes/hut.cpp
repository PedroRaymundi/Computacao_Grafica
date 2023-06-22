#include <customLib/scenes/hut.hpp>
#include <cmath>

hut_scene::hut_scene (GLuint program, GLuint* buffer) {
    this->program = program;
    this->buffer = buffer;

    std::vector<texture_info> textures; //Vetor auxiliar de informacoes de texturas usadas na malha
    
    //Criacao do modelo da malha de cabana com suas respectivas texturas
    textures.push_back({"../obj/cabana/WoodCabinDif.jpg",GL_RGB});
    textures.push_back({"../obj/cabana/WoodCabinDif.jpg",GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/cabana/cabana.obj", textures, v_vertices, v_normals, v_uvs));
    textures.clear();

    //Criacao do modelo da malha do terreno externo de areia com sua respectiva textura
    textures.push_back({"../obj/terreno/areia.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/terreno/terreno.obj", textures, v_vertices, v_normals, v_uvs));
    textures.clear();

	// Criacao do modelo da skybox
    textures.push_back({"../obj/skybox/dark_horizon.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/skybox/sky.obj", textures, v_vertices, v_normals, v_uvs));
    textures.clear();
	
	// Criacao do modelo do nosso lobo awoooo
	textures.push_back({"../obj/wolf/tex.jpg", GL_RGB});
	//textures.push_back({"../obj/wolf/tex.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/wolf/model_fixtriangle.obj", textures, v_vertices, v_normals, v_uvs, false, true));
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

float my_global = 0;

void hut_scene::update(glm::vec3 pos, glm::vec3 projection) {
    //atualização da skybox para manter o player sempre ao centro dela
    //TODO atualizar a textura horrível que eu fiz pra skybox
	// TODO: insert the wolf following logic
	// scene_objects[3].m_model = wolf_follow(pos)
	// Wolf
	glm::mat4 wolf_model = glm::scale(glm::mat4(1.0f), glm::vec3(0.02f, 0.02f, 0.02f));
	wolf_model = glm::translate(wolf_model, glm::vec3(cos(my_global) * 300.0f, 20.0f, sin(my_global) * 300.0f));
	my_global += 0.1;
	if (my_global > 3.14 * 2)
	{
		my_global = 0;
	}
	
	// Making the wolf follow the player
	// TODO: store the actual wolf position and make it go forward.
	wolf_model = glm::translate(wolf_model, pos);
	scene_objects[3].m_model = wolf_model;
    scene_objects[2].m_model = glm::translate(glm::mat4(1.0f), pos);
	
	// This is doing absolutely NOTHING....
    scene_objects[2].scale(50.0f, 50.0f, 50.0f); // TODO: the scale can be put inside the model matrix.
    for(int i = 0; i < scene_objects.size(); i++) {
        scene_objects[i].update();
    }
}