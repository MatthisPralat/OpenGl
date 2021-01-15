#ifndef cameraController_H
#define cameraController_H

#include <glad/glad.h>
// Mathematiques pour openGl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>// Standard input ouput  stream cout cin
#include <string>

class cameraController 
{
public:

    glm::vec3 position = glm::vec3(0.0f, 0.5f, -0.5f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float fov = 45.0f;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float speed = 2.5f;

    glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(position, position + forward, up);

    cameraController() {}; // Ma camera avec les valeurs de bases

    //cameraController( glm::vec3 newPosition) // Ma camera avec une autre position 
    //{
    //    position = newPosition;
    //}

    void sayhello() 
    {

        std::cout << "hello";
    }

    // CAMERA CONTROLS

    void goForward( float deltaTime)
    {
        position += forward * speed * deltaTime;
    }

    void goRight(float deltaTime) 
    {
        position -= glm::normalize(glm::cross(forward, up)) * speed * deltaTime;
    }

    void updateView()
    {
        view = glm::lookAt(position, position + forward, up);
    }
  
  
    void zoom(float yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 175.0f)
            fov = 175.0f;

        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
    }
    void rotate(float rotateAngle, glm::vec3 rotateVector) 
    {
        view = glm::rotate(view, glm::radians(rotateAngle), rotateVector);

    }

    void cameraMouse(float xoffset, float yoffset)
    {
        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch) );
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(direction);
       
    };

        

};


#endif