// Ce fichier regroupe la construction de geometries brut 
#include "myGeo.h"
#include <glad/glad.h>

#include "shader_s.h"
#include <iostream>// Standard input ouput  stream cout cin
#include <string>
#include <tuple>

// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



float CubeVertices[] = {
    //positions             colors               texture coords     normals
    //X     Y       Z       R      G    B        U      V
    // Back Plane
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,         0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 0.0f,         0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 2.0f,         0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 2.0f,         0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 2.0f,         0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,         0.0f,  0.0f, -1.0f,

    // Front Plane
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,         0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,         0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,         0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,         0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,         0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,         0.0f,  0.0f,  1.0f,

    // Right Plane
   -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,         -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,         -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,         -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,         -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,         -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,         -1.0f,  0.0f,  0.0f,

   //  Left plane
   0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,           1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,           1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,           1.0f,  0.0f,  0.0f,
   0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,           1.0f,  0.0f,  0.0f,

   // Bottom Plane
  -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,           0.0f, -1.0f,  0.0f,
   0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,           0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,           0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,           0.0f, -1.0f,  0.0f,

  // Top Plane
 -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,            0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,            0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,            0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,            0.0f,  1.0f,  0.0f,
 -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,            0.0f,  1.0f,  0.0f,
 -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,            0.0f,  1.0f,  0.0f
};


glm::vec3 cubesPositions[] = {
    glm::vec3(0.0f, 0.0f, -10.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

unsigned int CubeIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

float CubeTexCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

myGeo::myGeo()
{
    float cube[] = {0.0f,1.0f};
    float test = 20;
}

/**
* Ajout de 10 cubes test
*/
void myGeo::add10Cubestest(Shader objectShader, float time)
{

    //glBindVertexArray(VAO);


    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubesPositions[i]);
        float angle;
        if (i % 3 == 0)
        {
            angle = 20.0f * (i + 1) * (time * 0.5);
        }
        else
        {
            angle = -20.0f * (i + 1) * (time * 0.5);

        }
        // model = glm::rotate(model, glm::radians((float)glfwGetTime() / 10), glm::vec3(0.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        objectShader.SetMatrix4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
}

}

/**
* Ici je créé ma geometrie.
* Elle est répartie dans plusieurs Conteneurs differents:
* Vertex buffer object| Vertex array object | Element buffer object
*/
void myGeo::createGeo(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float geoVertices[], unsigned int geoIndices[])
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geoVertices), geoVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(geoIndices), geoIndices, GL_STATIC_DRAW);
    
   
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);


    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void myGeo::createCube(unsigned int& VBO, unsigned int& VAO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
   
    glBindVertexArray(VAO);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Normal position
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

}



