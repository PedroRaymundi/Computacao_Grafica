struct Knife
{
	glm::vec3 pos;
	bool taken = false;
	float rot;
	
	glm::mat4 knife_logic(glm::vec3 pos, glm::vec3 sight_direction)
	{
		glm::mat4 model(1.0f);
		
		glm::vec3 knife_pos;
		
		float scale;
		
		// If not taken, rotate around center
		if (!taken)
		{
			knife_pos = glm::vec3(10.0f, 0.0f, 10.0f);
			
			if (glm::length(pos - knife_pos) < 2.0f)
			{
				taken = true;
			}
			
			rot += 0.1f;
			if (rot > 3.141592 * 2)
				rot -= 3.141592 * 2;
			
			scale = 0.25f;
		}
		
		// Else, follow player's sight
		else
		{
			knife_pos = pos + sight_direction * 0.2f;
			
			scale = 0.03f;
		}
		
		model = glm::translate(model, knife_pos);
		model = glm::scale(model, glm::vec3(scale));
		//model = glm::rotate(model, rot, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 3.1415f / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		return model;
	}
};
