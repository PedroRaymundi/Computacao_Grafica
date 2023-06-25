#define _USE_MATH_DEFINES

#include <customLib/scenes/hut.hpp>
#include <cmath>

float randFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

glm::vec3 randWolf()
{
	return glm::vec3(randFloat() * 10 - 5, 0.0f, randFloat() * 10 - 5);
}

hut_scene::hut_scene (GLuint program, GLuint* buffer) {
    this->program = program;
    this->buffer = buffer;

    std::vector<texture_info> textures; //Vetor auxiliar de informacoes de texturas usadas na malha
    
    //Criacao do modelo da malha de cabana com suas respectivas texturas
    textures.push_back({"../obj/casa/casa.jpg",GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/casa/casa.obj", textures, v_vertices, v_normals, v_uvs));
    textures.clear();

	// Criacao do modelo da skybox
    textures.push_back({"../obj/skybox/dark_horizon.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/skybox/sky.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();
	
    textures.push_back({"../obj/caixas/caixa.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/caixas/caixa_fix.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

	// Faquinha pra matar os lobiño
	textures.push_back({"../obj/knife/tex.jpg", GL_RGB});
	textures.push_back({"../obj/knife/tex.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/knife/model_fix.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

    // terreno
	textures.push_back({"../obj/terreno/grama.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/terreno/terreno.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();
    textures.push_back({"../obj/terreno/pedras.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/terreno/terreno.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

    //arvore
    textures.push_back({"../obj/arvore/arvore.jpg", GL_RGB});
    textures.push_back({"../obj/arvore/arvore.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/arvore/DeadTree_fix.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

    //arvore
    textures.push_back({"../obj/arvore/arvore.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/arvore/arvre.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

    //mochila
    textures.push_back({"../obj/mochila/mochila.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/mochila/mochila.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();
    
    //vhs
    textures.push_back({"../obj/mesa/vhs.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/mesa/vhs.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();

	wolf_start = 10;
	// Criacao do modelo do nosso lobo awoooo
	textures.push_back({"../obj/wolf/tex.jpg", GL_RGB});
	textures.push_back({"../obj/wolf/tex.jpg", GL_RGB});
    scene_objects.push_back(mesh(program, "../obj/wolf/model_fixtriangle.obj", textures, v_vertices, v_normals, v_uvs, false, true));
	
	// Criacao do modelo do nosso lobo awoooo
    scene_objects.push_back(mesh(program, "../obj/wolf/model_fixtriangle.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    scene_objects.push_back(mesh(program, "../obj/wolf/model_fixtriangle.obj", textures, v_vertices, v_normals, v_uvs, false, true));
    textures.clear();
	wolves.resize(3); // We have 3 wolves.
	
    //Envia o vetor de coordenadas dos vertices do cenario para a GPU
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
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

    // Upload coordenadas normals de cada vertice
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, v_normals.size()  * sizeof(glm::vec3), &v_normals[0], GL_STATIC_DRAW);
    GLint loc_normals_coord = glGetAttribLocation(program, "normals");
    glEnableVertexAttribArray(loc_normals_coord);
    glVertexAttribPointer(loc_normals_coord, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) 0);

    //luz info
    GLint loc_light_pos = glGetUniformLocation(program, "lightPos"); // recuperando localizacao da variavel lightPos na GPU
    glUniform3f(loc_light_pos, 0.0f, 3.5f, 0.0f); // posicao da fonte de luz

    GLint loc_ka = glGetUniformLocation(program, "ka"); // recuperando localizacao da variavel ka na GPU
    glUniform1f(loc_ka, 0.3); // envia ka pra gpu
    GLint loc_kd = glGetUniformLocation(program, "kd"); // recuperando localizacao da variavel ka na GPU
    glUniform1f(loc_kd, 0.3); // envia kd pra gpu   
    GLint loc_ks = glGetUniformLocation(program, "ks"); // recuperando localizacao da variavel ks na GPU
    glUniform1f(loc_ks, 0.9); // envia ks pra gpu        
    GLint loc_ns = glGetUniformLocation(program, "ns"); // recuperando localizacao da variavel ns na GPU
    glUniform1f(loc_ns, 32); // envia ns pra gpu  

    //positioning, rotating and scaling objects
    //hut
    scene_objects[0].scale(0.4f,0.4f,0.4f);
    scene_objects[0].translate(0.0f, -2.0f, 0.0f);
    //skybox
    scene_objects[1].scale(15.0f, 15.0f, 15.0f);	
	//caixas
    scene_objects[2].scale(1.0f, 1.0f, 1.0f);
    scene_objects[2].translate(2.0f, 0.5f, 0.0f);
	//faca
	scene_objects[3].scale(10.0f, 10.0f, 10.0f);
    //terreno
	scene_objects[4].scale(20.0f, 0.1f, 20.0f);
    scene_objects[4].translate(0.0f, -10.0f, 0.0f);
    scene_objects[5].scale(5.0f, 0.1f, 15.0f);
    scene_objects[5].translate(0.0f, -9.9f, -0.2f);
    //arvore
    scene_objects[6].translate(10.0f, -1.0f, -0.2f);
    scene_objects[6].scale(0.5f, 0.5f, 0.5f);
    scene_objects[7].translate(-8.0f, -3.0f, 7.2f);
    //mochila
    scene_objects[8].scale(0.8f, 0.8f, 0.8f);
    scene_objects[8].translate(2.5f, -1.0f, 1.5f);
    //vhs
    scene_objects[9].translate(0.0f, -0.5f, -1.0f);
}

glm::vec3 wolf_pos(0.0f, 1.0f, 0.0f);
glm::vec3 wolf_ori(0.0f);
float light_angle = 0.0f;

glm::mat4 hut_scene::wolf_logic(glm::vec3 pos, size_t w, bool started)
{
	if (!started)
	{
		return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));
	}
	
	Wolf wolfy = wolves[w];
	glm::vec3 wolf_pos = wolfy.pos;
	
	float y_rot;
	glm::vec3 diff = pos - wolf_pos;
	diff = glm::normalize(glm::vec3(diff.x, 0, diff.z));
	y_rot = asin(diff.x) > 0 ? acos(diff.z) : acos(diff.z) * -1.0f;
	
	//printf("timer for %d: %d\n", w, wolves_timer[w]);
	
	// Only move for and undertermined period of time
	if (wolfy.timer < 0)
	{
		//printf("updating wolf position\n");
		
		if (!wolfy.dead) wolf_pos += diff * 0.03f;
		
		if (wolfy.timer < -100)
		{
			wolfy.noise = glm::normalize(randWolf());
			wolfy.timer = rand() % 1000;
		}
	}
	
	wolfy.timer -= 1;
	
	if (!wolfy.dead)
	{
		wolf_pos += wolfy.noise * 0.003f;
		wolfy.pos = wolf_pos;		
	}
	else
	{
		wolfy.pos = glm::vec3(wolf_pos.x, -10.0f, wolf_pos.z);
	}
	wolves[w] = wolfy;
	
	glm::mat4 wolf_model;

	// Making the wolf follow the player
	wolf_model = glm::mat4(1.0f);
	wolf_model = glm::translate(wolf_model, wolf_pos);
	
	if (!wolfy.dead)
	{
		wolf_model = glm::rotate(wolf_model, y_rot, glm::vec3(0.0f, 1.0f, 0.0f)); //  - 3.14f/2.0f		
	}
	
	return wolf_model;
}
float change = 0;
void hut_scene::update(glm::vec3 pos, glm::vec3 projection, app user_control) {

	// Rotating the light source
    GLint loc_light_pos = glGetUniformLocation(program, "lightPos"); // recuperando localizacao da variavel lightPos na GPU

	light_angle += 0.0007;
	if (light_angle > M_PI * 2.0f)
		light_angle -= M_PI * 2;

	glm::vec3 sun_pos = glm::vec3(5.0 * cos(light_angle), 5.0f * cos(light_angle) + 2.5, 5.0 * sin(light_angle));
	glUniform3f(loc_light_pos, sun_pos.x, sun_pos.y, sun_pos.z); // posicao da fonte de luz

    //TODO atualizar a textura horrível que eu fiz pra skybox
	// TODO: insert the wolf following logic
	// Wolf
	
	for (size_t idx = 0 ; idx < wolves.size() ; idx++)
	{
		// Check if wolf should be dead.
		if (wolf_killer_knife.taken && glm::length(pos - wolves[idx].pos) < 2.5f && user_control.key_state[' '] ==GLFW_PRESS)
		{
			wolves[idx].dead = true;
		}
		scene_objects[wolf_start + idx].m_model = wolf_logic(pos, idx, wolf_killer_knife.taken);
		scene_objects[wolf_start + idx].scale(0.03f, 0.03f, 0.03f);
	}

	//wolf_model = glm::scale(wolf_model, glm::vec3(0.02f, 0.02f, 0.02f));
	
    //GLint loc_light_pos = glGetUniformLocation(program, "lightPos"); // recuperando localizacao da variavel lightPos na GPU
    //glUniform3f(loc_light_pos, wolf_pos.x, wolf_pos.y, wolf_pos.z); // posicao da fonte de luz
	
    //atualização da skybox para manter o player sempre ao centro dela
    scene_objects[1].m_model = glm::translate(glm::mat4(1.0f), pos);
    scene_objects[1].scale(50.0f, 50.0f, 50.0f);

    scene_objects[3].m_model = wolf_killer_knife.knife_logic(pos, projection);

    for(int i = 0; i < scene_objects.size(); i++) {
        scene_objects[i].update(i >= wolf_start && i < (wolf_start + wolves.size()));
    }
}
