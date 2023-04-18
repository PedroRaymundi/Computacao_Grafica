#include "customLib/actors.hpp"

ship::ship(int _start_position_on_vector) : speed(0) {

    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;
    base_object base_ship(4, end_position_on_vector);
    base_ship.vertices[0] = { +0.0f, +0.5f }; 
    base_ship.vertices[1] = { +0.45f, -0.45f };
    base_ship.vertices[2] = { +0.0f, -0.3f };
    base_ship.vertices[3] = { -0.45f, -0.45f };
    base_ship.R = 0.5;
    base_ship.G = 0.5;
    base_ship.B = 0.5;
    object_element.push_back(base_ship);
    end_position_on_vector += base_ship.nvertices;

    base_object window(4, end_position_on_vector);
    window.vertices[0] = { +0.00f, +0.4f }; 
    window.vertices[1] = { +0.25f, -0.25f };
    window.vertices[2] = { +0.00f, -0.15f };
    window.vertices[3] = { -0.25f, -0.25f };
    window.R = 0.25;
    window.G = 0.25;
    window.B = 1.0;
    object_element.push_back(window);
    end_position_on_vector += window.nvertices;

    base_object dk(3, end_position_on_vector);
    dk.vertices[0] = { +0.00f, -0.1f }; 
    dk.vertices[1] = { +0.15f, -0.3f };
    dk.vertices[2] = { -0.15f, -0.3f };
    dk.R = 0.0;
    dk.G = 0.0;
    dk.B = 0.0;
    object_element.push_back(dk);
    end_position_on_vector += dk.nvertices;
}

void ship::movement(GLFWwindow* window, int key, int scancode, int action, int mods) {
    printf("Pressionando tecla %d\naction: %d\n\n", key, action);
    switch (key) {
    case GLFW_KEY_SPACE:
        if(action) {
            //speed = 0.01;
        } else {
            //speed = 0;
        }
        break;
    
    default:
        break;
    }
}

meteor::meteor(int _start_position_on_vector) {
    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;
    base_object base_meteor(6, end_position_on_vector);
    base_meteor.vertices[0] = { +0.0f, +0.2f }; 
    base_meteor.vertices[1] = { +0.2f, +0.1f };
    base_meteor.vertices[2] = { +0.6f, +0.0f };
    base_meteor.vertices[3] = { +0.7f, +0.4f };
    base_meteor.vertices[4] = { +0.4f, +0.5f };
    base_meteor.vertices[5] = { +0.1f, +0.4f };
    base_meteor.R = 0.25;
    base_meteor.G = 0.25;
    base_meteor.B = 0.25;
    object_element.push_back(base_meteor);
    end_position_on_vector += base_meteor.nvertices;

}

planet::planet(int _start_position_on_vector) {
    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;
    
    //Objeto principal de fundo do planeta
    base_object base_planet(32, end_position_on_vector);
    float partition = 2*M_PI/32;

    for (int i = 0; i < 32; i++){
        base_planet.vertices[i].x = 0.3 * sin(partition*i);
        base_planet.vertices[i].y = 0.3 * cos(partition*i);

        std::cout << base_planet.vertices[i].x << "\n";
        std::cout << base_planet.vertices[i].y << "\n";
    }
    
    base_planet.R = 0.50;
    base_planet.G = 0.20;
    base_planet.B = 0.0;
    object_element.push_back(base_planet);
    end_position_on_vector += base_planet.nvertices;

    //Mancha 1 do planeta
    base_object crater_1(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_1.vertices[i].x = 0.2 + (0.07 * sin(partition*i));
        crater_1.vertices[i].y = 0.1 + (0.07 * cos(partition*i));

        std::cout << crater_1.vertices[i].x << "\n";
        std::cout << crater_1.vertices[i].y << "\n";
    }
    
    crater_1.R = 0.70;
    crater_1.G = 0.20;
    crater_1.B = 0.0;
    object_element.push_back(crater_1);
    end_position_on_vector += crater_1.nvertices;

}