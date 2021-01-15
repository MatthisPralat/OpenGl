/*******************************************************************
** This part will process all the event of our application
** Key pressed
** Mouse Position
** Window Resise
******************************************************************/
#ifndef EVENTS_H
#define EVENTS_H

#include <glad/glad.h> // Remplis les adresses
#include <GLFW/glfw3.h> // Gere la fenetre et les evenement 


#include <string>
#include <tuple>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class events
{
public:
    
    float time, currentFrame, deltaTime, lastFrame;
    
    // Window
    float windowSizeX, windowSizeY;

    // Mouse
    bool firstMouse = true;
    bool mouseIsMoving = false;
    float lastMouseX= 400, lastMouseY = 300;
    float MouseOffsetX, MouseOffsetY;
    float mouseSensivity = 0.1f;
    float mouseScroll;


    float windowsX, windowsY;

    
    // constructor
    events(){};

    void init(GLFWwindow* window){
    
        std::cout << window ;
        //glfwSetCursorPosCallback(window, this->my_mouse_callback);

    };

    void update(){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

    };

    std::tuple<float, float> getWindowSize(float x, float y)
    {
       
        return {x,y};
    }

    void mousePosition(double xpos, double ypos)
    {

        if (firstMouse)
        {
            lastMouseX = xpos;
            lastMouseY = ypos;
            firstMouse = false;
            MouseOffsetX = -90;
            MouseOffsetY = -22.5;
        }
        else 
        {
        MouseOffsetX = xpos - lastMouseX;
        MouseOffsetY = lastMouseY - ypos;
        lastMouseX = xpos;
        lastMouseY = ypos;

        MouseOffsetX *= mouseSensivity;
        MouseOffsetY *= mouseSensivity;
        }
    }

};

#endif