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

meteor::meteor(int _start_position_on_vector) {
    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;

    //Calda do meteoro
    base_object calda_meteoro(24, end_position_on_vector);
    float partition = 2*M_PI/32;

    for (int i = 0; i < 18; i++){
        calda_meteoro.vertices[i].x = 0.24 * sin(partition*i);
        calda_meteoro.vertices[i].y = 0.24 * cos(partition*i);
    }

    
    calda_meteoro.vertices[18] = {-0.6f,-0.1f};
    calda_meteoro.vertices[19] = {-0.4f,-0.02f};
    calda_meteoro.vertices[20] = {-0.8f,0};
    calda_meteoro.vertices[21] = {-0.4f,0.02f};
    calda_meteoro.vertices[22] = {-0.6f,0.1f};

    calda_meteoro.vertices[23].x = 0.24 * sin(partition*31);
    calda_meteoro.vertices[23].y = 0.24 * cos(partition*31);

    calda_meteoro.R = 0.9;
    calda_meteoro.G = 0.9;
    calda_meteoro.B = 0.9;

    object_element.push_back(calda_meteoro);
    end_position_on_vector += calda_meteoro.nvertices;

    //Base do meteoro
    base_object base_meteor(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        base_meteor.vertices[i].x = 0.2 * sin(partition*i);
        base_meteor.vertices[i].y = 0.2 * cos(partition*i);
    }

    base_meteor.R = 0.25;
    base_meteor.G = 0.25;
    base_meteor.B = 0.25;

    object_element.push_back(base_meteor);
    end_position_on_vector += base_meteor.nvertices;

    //Mancha 1 meteoro
    base_object mancha_meteoro_1(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        mancha_meteoro_1.vertices[i].x = 0.1 + (0.03 * sin(partition*i));
        mancha_meteoro_1.vertices[i].y = 0.1 + (0.03 * cos(partition*i));

    }

    mancha_meteoro_1.R = 0.8;
    mancha_meteoro_1.G = 0.8;
    mancha_meteoro_1.B = 0.8;

    object_element.push_back(mancha_meteoro_1);
    end_position_on_vector += mancha_meteoro_1.nvertices;

    //Mancha 2 meteoro
    base_object mancha_meteoro_2(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        mancha_meteoro_2.vertices[i].x = 0.02 + (0.03 * sin(partition*i));
        mancha_meteoro_2.vertices[i].y = 0.15 + (0.02 * cos(partition*i));

    }

    mancha_meteoro_2.R = 0.8;
    mancha_meteoro_2.G = 0.8;
    mancha_meteoro_2.B = 0.8;

    object_element.push_back(mancha_meteoro_2);
    end_position_on_vector += mancha_meteoro_2.nvertices;

}

alien::alien(int _start_position_on_vector) {
    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;
    
    //Parte 1 cabeça alien
    base_object alien_head_1(32, end_position_on_vector);
    float partition = 2*M_PI/32;

    for (int i = 0; i < 32; i++){
        alien_head_1.vertices[i].x = 0.2 * sin(partition*i);
        alien_head_1.vertices[i].y = 0.2 * cos(partition*i);
    }

    alien_head_1.R = 0;
    alien_head_1.G = 0.8;
    alien_head_1.B = 0;
    object_element.push_back(alien_head_1);
    end_position_on_vector += alien_head_1.nvertices;

    //Parte 2 cabeça alien
    base_object alien_head_2(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        alien_head_2.vertices[i].x = 0.18 * sin(partition*i) ;
        alien_head_2.vertices[i].y = 0.18 * cos(partition*i) - 0.08;
    }

    alien_head_2.R = 0;
    alien_head_2.G = 0.8;
    alien_head_2.B = 0;
    object_element.push_back(alien_head_2);
    end_position_on_vector += alien_head_2.nvertices;

    //Olho 1 alien
    base_object alien_eye_1(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        alien_eye_1.vertices[i].x = 0.06 * sin(partition*i) - 0.08;
        alien_eye_1.vertices[i].y = 0.04 * cos(partition*i);
    }

    alien_eye_1.R = 0;
    alien_eye_1.G = 0;
    alien_eye_1.B = 0;
    object_element.push_back(alien_eye_1);
    end_position_on_vector += alien_eye_1.nvertices;

    //Olho 2 alien
    base_object alien_eye_2(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        alien_eye_2.vertices[i].x = 0.06 * sin(partition*i) + 0.08;
        alien_eye_2.vertices[i].y = 0.04 * cos(partition*i);
    }

    alien_eye_2.R = 0;
    alien_eye_2.G = 0;
    alien_eye_2.B = 0;
    object_element.push_back(alien_eye_2);
    end_position_on_vector += alien_eye_2.nvertices;

    //Branco do olho 1 do alien
    base_object alien_white_eye_1(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        alien_white_eye_1.vertices[i].x = 0.01 * sin(partition*i) - 0.06;
        alien_white_eye_1.vertices[i].y = 0.01 * cos(partition*i);
    }

    alien_white_eye_1.R = 1;
    alien_white_eye_1.G = 1;
    alien_white_eye_1.B = 1;
    object_element.push_back(alien_white_eye_1);
    end_position_on_vector += alien_white_eye_1.nvertices;

    //Branco do olho 2 do alien
    base_object alien_white_eye_2(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        alien_white_eye_2.vertices[i].x = 0.01 * sin(partition*i) + 0.1;
        alien_white_eye_2.vertices[i].y = 0.01 * cos(partition*i);
    }

    alien_white_eye_2.R = 1;
    alien_white_eye_2.G = 1;
    alien_white_eye_2.B = 1;
    object_element.push_back(alien_white_eye_2);
    end_position_on_vector += alien_white_eye_2.nvertices;

}

star::star(int _start_position_on_vector) {
    start_position_on_vector = _start_position_on_vector;
    end_position_on_vector = start_position_on_vector;
    
    // Miolo da estrela
    base_object star(5, end_position_on_vector);
    
    star.vertices[0] = {0.00, 0.25};
    star.vertices[1] = {0.24, 0.08};
    star.vertices[2] = {0.14, -0.20};
    star.vertices[3] = {-0.14, -0.20};
    star.vertices[4] = {-0.24, 0.08};

    star.R = 1;
    star.G = 1;
    star.B = 0.0;
    object_element.push_back(star);
    end_position_on_vector += star.nvertices;

    // Ponta 1 da estrela
    base_object star_point_1(3, end_position_on_vector);
    
    star_point_1.vertices[0] = {0.14f, -0.20f}; 
    star_point_1.vertices[1] = {0.00f, -0.6f};
    star_point_1.vertices[2] = {-0.14f, -0.20f};

    star_point_1.R = 1;
    star_point_1.G = 1;
    star_point_1.B = 0.0;
    object_element.push_back(star_point_1);
    end_position_on_vector += star_point_1.nvertices;

    // Ponta 2 da estrela
    base_object star_point_2(3, end_position_on_vector);
    
    star_point_2.vertices[0] = {0.00f, 0.25f}; 
    star_point_2.vertices[1] = {0.41f, 0.58f};
    star_point_2.vertices[2] = {0.24f, 0.08f};

    star_point_2.R = 1;
    star_point_2.G = 1;
    star_point_2.B = 0.0;
    object_element.push_back(star_point_2);
    end_position_on_vector += star_point_2.nvertices;

    // Ponta 3 da estrela
    base_object star_point_3(3, end_position_on_vector);
    
    star_point_3.vertices[0] = {-0.24, 0.08}; 
    star_point_3.vertices[1] = {-0.41f, 0.58f};
    star_point_3.vertices[2] = {0.00, 0.25};

    star_point_3.R = 1;
    star_point_3.G = 1;
    star_point_3.B = 0.0;
    object_element.push_back(star_point_3);
    end_position_on_vector += star_point_3.nvertices;

    // Ponta 4 da estrela
    base_object star_point_4(3, end_position_on_vector);
    
    star_point_4.vertices[0] = {-0.14, -0.20}; 
    star_point_4.vertices[1] = {-0.6f, -0.2f};
    star_point_4.vertices[2] = {-0.24, 0.08};

    star_point_4.R = 1;
    star_point_4.G = 1;
    star_point_4.B = 0.0;
    object_element.push_back(star_point_4);
    end_position_on_vector += star_point_4.nvertices;

    // Ponta 5 da estrela
    base_object star_point_5(3, end_position_on_vector);
    
    star_point_5.vertices[0] = {0.24, 0.08}; 
    star_point_5.vertices[1] = {0.6f, -0.20f};
    star_point_5.vertices[2] = {0.14, -0.20};

    star_point_5.R = 1;
    star_point_5.G = 1;
    star_point_5.B = 0.0;
    object_element.push_back(star_point_5);
    end_position_on_vector += star_point_5.nvertices;

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
    }
    
    base_planet.R = 1;
    base_planet.G = 0.40;
    base_planet.B = 0.0;
    object_element.push_back(base_planet);
    end_position_on_vector += base_planet.nvertices;

    //Mancha 1 do planeta
    base_object crater_1(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_1.vertices[i].x = 0.12 + (0.08 * sin(partition*i));
        crater_1.vertices[i].y = 0.14 + (0.08 * cos(partition*i));
    }
    
    crater_1.R = 1;
    crater_1.G = 0.6;
    crater_1.B = 0.2;
    object_element.push_back(crater_1);
    end_position_on_vector += crater_1.nvertices;

    //Mancha 2 do planeta 
    base_object crater_2(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_2.vertices[i].x = 0.02 + (0.04 * sin(partition*i));
        crater_2.vertices[i].y = 0.23 + (0.04 * cos(partition*i));
    }
    
    crater_2.R = 1;
    crater_2.G = 0.80;
    crater_2.B = 0.4;
    object_element.push_back(crater_2);
    end_position_on_vector += crater_2.nvertices;

    //Mancha 3 do planeta
    base_object crater_3(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_3.vertices[i].x =  (0.05 * sin(partition*i)) - 0.14 ;
        crater_3.vertices[i].y =  (0.05 * cos(partition*i)) - 0.16;
    }
    
    crater_3.R = 1;
    crater_3.G = 0.60;
    crater_3.B = 0.2;
    object_element.push_back(crater_3);
    end_position_on_vector += crater_3.nvertices;

    //Mancha 4 do planeta 
    base_object crater_4(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_4.vertices[i].x = (0.03 * sin(partition*i)) - 0.05;
        crater_4.vertices[i].y = (0.03 * cos(partition*i)) - 0.25;
    }

    crater_4.R = 1;
    crater_4.G = 0.80;
    crater_4.B = 0.4;
    object_element.push_back(crater_4);
    end_position_on_vector += crater_4.nvertices;

    //Mancha 5 do planeta 
    base_object crater_5(32, end_position_on_vector);

    for (int i = 0; i < 32; i++){
        crater_5.vertices[i].x = (0.05 * sin(partition*i)) - 0.18;
        crater_5.vertices[i].y = 0.14 + (0.05 * cos(partition*i));
    }

    crater_5.R = 1;
    crater_5.G = 0.6;
    crater_5.B = 0.2;
    object_element.push_back(crater_5);
    end_position_on_vector += crater_5.nvertices;

}