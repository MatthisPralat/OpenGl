#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <glad/glad.h>
// Gestions de fenetres, de peripheriques pour opengl
#include <GLFW/glfw3.h>
// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Permet de lire les image .png , .jpg , ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>// Standard input ouput  stream cout cin
#include <string>
#include "events.h"

class myOpenGL 
{
public:
    myOpenGL() {}; // Ma camera avec les valeurs de bases
    void setWindowHint()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    };

    int createWindow(GLFWwindow* window)
    {
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
    }

    /**
    * Va remplir les adresses des fonctions de GLFW et OPENGL pour les utiliser
    */
    int gladLoad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
    }

    void loadTexture(unsigned int& texture1, const char* filename)
    {
        // load and create a texture 
        // -------------------------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // set texture filtering parameters int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        int width, height, nrChannels;
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
        //int width, height, nrChannels;
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

};
#endif