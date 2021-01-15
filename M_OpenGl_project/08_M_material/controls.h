#ifndef CONTROLS_H
#define CONTROLS_H

#include <glad/glad.h>
// Gestions de fenetres, de peripheriques pour opengl
#include <GLFW/glfw3.h>
// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>// Standard input ouput  stream cout cin
#include <string>
/**
* Cette classe va ecouter les periferiques et renvoyer des actions
*
*/
#include "cameraController.h" // Gere la camera par une matrice
#include "events.h"

class controls 
{
public:
    controls() {}; // Ma camera avec les valeurs de bases
    

    //cameraController* CameraPtr; // Adresse à referencer pour la cam
    //events* eventsPtr; // Adresse à referencer pour les evenements

    void mouseMove(cameraController& camera, events& events){ camera.cameraMouse(events.MouseOffsetX, events.MouseOffsetY); };

    void goForward(cameraController& camera, events& events){camera.goForward(events.deltaTime);};
    void goBackward(cameraController& camera, events& events){camera.goForward(- events.deltaTime);};
    void goRight(cameraController& camera, events& events){camera.goRight(events.deltaTime);};
    void goLeft(cameraController& camera, events& events) { camera.goRight(- events.deltaTime); };
    
    void exit(GLFWwindow* window){ glfwSetWindowShouldClose(window, true); };

};
#endif