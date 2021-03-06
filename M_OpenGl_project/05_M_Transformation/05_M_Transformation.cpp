#include<iostream>
#include<string>
// -----------------------------------
//  HEADER OPENGL
// -----------------------------------

// Lib de base c++ pour faire ecrire dans la console ou avoir des variable string a partir de char

// Va remplir toutes les adresses de OpenGl et GlfW (peut etre)
#include <glad/glad.h>
// Gestions de fenetres, de peripheriques pour opengl
#include <GLFW/glfw3.h>
// 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Permet de lire les image .png , .jpg , ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Classe pour compiler des shader et le lier � openGl
#include "shader_s.h"




// VAR
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE = "LearnOpenGL";

float mixValue = 0.2f;

//--------------------------------
// OUR GEOMETRY 
//--------------------------------

float vertices[] = {
    // positions            // colors           // texture coords
    //X     Y       Z       R      G    B        U      V
    // Back Plane
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 2.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   2.0f, 2.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 2.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

    // Front Plane
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    
     // Right Plane
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     
     //  Left plane
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    
     // Bottom Plane
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    
     // Top Plane
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f
};


glm::vec3 cubePositions[] = {
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

unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

//--------------------------------

void debugMath()
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    //int test = 2;
    //std::cout << vec.x << vec.y << vec.z << std::endl;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
};


/**
* Retourne les inputs qui sont pr�ss�s ou relach�s
*/
void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
}

/**
* Retourne la taille de la fenetre opengl, donc le nombres de pixel � afficher
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void setWindowHint()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int createWindow(GLFWwindow* window)
{
     if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

unsigned char* LoadGlTexture(const char* file, int width, int height, int nrChannels, unsigned char* data)
{
    //int width, height, nrChannels;
    stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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
    return data;
}


/**
* Ici je cr�� ma geometrie.
* Elle est r�partie dans plusieurs Conteneurs differents:
* Vertex buffer object| Vertex array object | Element buffer object
*/
void createGeo(unsigned int&  VBO, unsigned int&  VAO, unsigned int&  EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

void loadTextureExemple(unsigned int& texture1, unsigned int& texture2)
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
    const char* filename = "container.jpg";
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

    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

/**
* La fonction d'entree de notre programme openGL
*/
int main()
{
    glfwInit(); // initialisation de la bibliotheque glfw
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    createWindow(window);
    gladLoad();


    //Mon shader compil�
    Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

    //Mon model ---- 
    glm::mat4 model = glm::mat4(1.0f); // mon model est dans une matrice d'identit�e (1 en diagonale)
    model = glm::rotate(model, glm::radians(-55.0f),glm::vec3(1.0f, 0.0f, 0.0f)); // Je le tourne sur l'axe x de -55 radians

    // Ma Vue
    glm::mat4 view = glm::mat4(1.0f);// La je cr�� une matrice d'identit�e (1 en diagonale)
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0)); // J'avance ma scene de 3 m en Z (pour reculer ma camera de 3m)
    
    // Ma projection en perspective
    glm::mat4 projection; // Je cr�� une nouvelle matrice de projection
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Ma geometrie
    unsigned int VBO, VAO, EBO;
    createGeo(VBO, VAO, EBO);

    // Mes textures
    unsigned int texture1, texture2;
    loadTextureExemple(texture1, texture2);

    // Mon shader va uiliser la texture
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        glEnable(GL_DEPTH_TEST);

        glm::mat4 trans = glm::mat4(1.0f);
        std::cout << (float)glfwGetTime();
        
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
      
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.setFloat("mixValue", mixValue);

       // view = glm::rotate(view, glm::radians( glfwGetTime() * 1), glm::vec3(1.0f, 0.3f, 0.5f));
        float viewangle = 20.0f * 0 * (glfwGetTime() * 0.5);
        view = glm::rotate(view, glm::radians(viewangle), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle;
            if(i%3 == 0) 
            {
                angle = 20.0f * (i + 1) * (glfwGetTime() * 0.5);
            }
            else 
            {
                angle = -20.0f * (i + 1) * (glfwGetTime() * 0.5);

            }
            // model = glm::rotate(model, glm::radians((float)glfwGetTime() / 10), glm::vec3(0.0, 0.0, 1.0));
            model = glm::rotate(model, glm::radians(angle),
            glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    // load image, create texture and generate mipmaps

}