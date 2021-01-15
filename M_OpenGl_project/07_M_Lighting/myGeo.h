#ifndef MYGEO_H
#define MYGEO_H

#include <glad/glad.h>
#include "shader_s.h"
#include <iostream>// Standard input ouput  stream cout cin
#include <string>

// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class myGeo
{

public:

    myGeo();
    
    void add10Cubestest(Shader objectShader, float time);
    void createGeo(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO, float geoVertices[], unsigned int geoIndices[]);
    void createCube(unsigned int& VBO, unsigned int& VAO);
    

};
#endif