
// -----------------------------------
//  HEADER OPENGL
// -----------------------------------
// -----------
// First party
// -----------
// Lib de base c++ pour faire ecrire dans la console ou avoir des variable string a partir de char
#include<iostream>
#include<string>
#include <tuple>
// -----------
// Librairies externes 
// -----------
// Va remplir toutes les adresses de OpenGl et GlfW (peut etre)
#include <glad/glad.h>
// Gestions de fenetres, de peripheriques pour opengl
#include <GLFW/glfw3.h>
// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Permet de lire les image .png , .jpg , ...
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

// -----------
// Mes classes
// -----------
#include "myOpenGL.h" // fonctions utiles pour openGL
#include "shader_s.h" // Classe pour compiler des shader et le lier à openGl
#include "cameraController.h" // Gere la camera par une matrice
#include "myGeo.h" // Créé et ajoute des Geometries
#include "events.h" // Ecoute Retourne les evenements (temps, position de la sourie)
#include "controls.h" // Actions selons les controles 

// -----------------------------------
//  VARIABLES UTILISABLE PARTOUT
// -----------------------------------
// VAR
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE = "LearnOpenGL";

// Mouse pos
float mixValue = 0.2f;

// Camera
glm::vec3 newpos = glm::vec3(0.0f, 0.0f, 3.0f);
cameraController mainCamera; // Gere la camera
myGeo geo; // Genere de la geometrie
events myEvents; // Ecoute tout les evenement
controls myControls;
myOpenGL myOpengl;


// CALLBACK ---- 
// Pour le moment je ne sais pas comment faire mes call back autre part

/**
* Retourne les inputs qui sont préssés ou relachés
*/
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { myControls.exit(window); };
    // Controls
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) myControls.goForward(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) myControls.goForward(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) myControls.goBackward(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) myControls.goBackward(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) myControls.goRight(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) myControls.goRight(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) myControls.goLeft(mainCamera, myEvents);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) myControls.goLeft(mainCamera, myEvents);  
}

/**
* Retourne la position de ma sourie quand la sourie bouge
*/
void new_mouse_callback(GLFWwindow* window, double xpos, double ypos){ 
    myEvents.mousePosition(xpos, ypos); 
    myControls.mouseMove(mainCamera, myEvents);
}

/**
* Retourne la taille de la fenetre opengl, donc le nombres de pixel à afficher
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    myEvents.windowSizeX = width;
    myEvents.windowSizeY = width;
}


/**
* Retourne le scroll de la sourie
*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mainCamera.zoom((float)yoffset);
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



/**
* La fonction d'entree de notre programme openGL
*/
int main()
{
    glfwInit(); // initialisation de la bibliotheque glfw
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    myEvents.windowSizeX = SCR_WIDTH;
    myEvents.windowSizeY = SCR_HEIGHT;

    myOpengl.createWindow(window);
    myOpengl.gladLoad();
    

    // CALLBACKS
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Verifie la taille de la fenetre
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Active le suivis de la sourie dans la fenetre
    glfwSetScrollCallback(window, scroll_callback);  // Active la fonction qui retourne la position de la sourie
    glfwSetCursorPosCallback(window, new_mouse_callback); 
    

    // Ma camera
    mainCamera.position = glm::vec3(0.0, 1.0, 3.0f);


    // Mes textures stokées dans la carte graphique
    unsigned int texture1, texture2;
    myOpengl.loadTexture(texture1, "container.jpg");
    myOpengl.loadTexture(texture2, "awesomeface.png");


    // Configuration de mon premier objet -----------
    unsigned int VBO, VAO;
    geo.createCube(VBO, VAO); // Creation d'un cube et asignes les adresses dans VBO et VAO
    
   
    Shader ourShader("shader.vs", "shader.fs");  //Mon shader compilé
  
    ourShader.Use(); // On Dit à la carte que j'utilise ce shader
    // Mon shader va uiliser la texture
    ourShader.SetInteger("texture1", 0);
    ourShader.SetInteger("texture2", 1);
    
    glm::vec3 lightColor = glm::vec3(0.5f, 0.5f, 0.5f);
    ourShader.SetVector3f("lightColor", lightColor);
    

    // Configuration de mon deuxieme objet -----------
    
    // Light element 
    unsigned int lightVBO, lightVAO;
    geo.createCube(VBO, lightVAO);
    

    Shader lightShader("shader_light.vs", "shader_light.fs"); 
    


   
    while (!glfwWindowShouldClose(window))
    {
        
        myEvents.update(); // Listen events
        processInput(window); // Listen Key
        
        mainCamera.updateView(); // Update camera transform
        
        ourShader.Use();
        
        // Frame change 
        glEnable(GL_DEPTH_TEST); // Use Depth test
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Replace previous color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear two buffer

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
      
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        //geo.add10Cubestest(ourShader, myEvents.currentFrame); // Creation d'un cube et asignes les adresses dans VBO et VAO

        float sinTime = std::sin(myEvents.currentFrame);
        float sinTime2 = std::sin(myEvents.currentFrame / 4.0) ;

        float cosTime = std::cos(myEvents.currentFrame);

        glm::vec3 lightPosition = glm::vec3(6.0f * cosTime, 0.5f, 6.0f * sinTime);
        
        // Shader set uniform
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.SetMatrix4("view", mainCamera.view);
        ourShader.SetMatrix4("projection", mainCamera.projection);
        ourShader.SetMatrix4("model", model);
        ourShader.SetVector3f("lightColor", glm::vec3(1.0f));
        ourShader.SetVector3f("lightPos", lightPosition);
        ourShader.SetVector3f("viewPos", mainCamera.position);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.Use();
        //geo.createCube(lightVBO, lightVAO, lightEBO);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::scale(model, glm::vec3(0.2f));
        lightModel = glm::translate(lightModel, lightPosition);
        
        lightShader.SetMatrix4("view", mainCamera.view);
        lightShader.SetMatrix4("projection", mainCamera.projection);
        lightShader.SetMatrix4("model", lightModel);
        

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}