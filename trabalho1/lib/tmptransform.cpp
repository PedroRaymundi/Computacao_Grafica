#include "customLib/tmptransform.hpp"

void multiply(float* mt1, float* mt2, float* dest) {
    float m_a[4][4];
    float m_b[4][4];
    float m_c[4][4]; // m_c = m_a * m_b

    int n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_a[i][j] = mt1[n];
            m_b[i][j] = mt2[n];
            n += 1;
        }
    }


    for(int i=0;i<4;i++){    
        for(int j=0;j<4;j++){
            m_c[i][j]=0.0;
            for(int k=0; k < 4; k++){
                m_c[i][j] += m_a[i][k]*m_b[k][j];    
            }
        }
    }

    // voltando a resposta para o formato do OpenGL
    n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            dest[n] = m_c[i][j];
            n += 1;
        }
    }
}

void translate(complex_object* obj, float new_x, float new_y) {
    float mat_translation[16] = {
        1.0f, 0.0f, 0.0f, new_x ,
        0.0f, 1.0f, 0.0f, new_y ,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    multiply(obj->transformation_matrix, mat_translation, obj->transformation_matrix);
}

void resize(complex_object* obj, float factor) {
    float mat_scale[16] = {
        factor, 0.0f, 0.0f, 0.0f ,
        0.0f, factor, 0.0f, 0.0f ,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    multiply(obj->transformation_matrix, mat_scale, obj->transformation_matrix);
}