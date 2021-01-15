#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader_s.h"


// FONCTIONS ---------------------------------------------
// Fonction pour le resize de la fenetre
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Fonction pour les key press
void processInput(GLFWwindow* window);

// VARIABLES -----------------------------------------------
// Variables settings
// la taille initiale de la fenetre
// unsigned pour être positif
// Const car nous n'allons pas la modifier
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE = "LearnOpenGL";

//SHADER -----------------------------------------------


/*
// Vertex shader ---
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_PointSize = 5.0f;\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   vertexColor = vec4(aColor, 1.0);" // set the output variable to a dark-red color
"}\0";

// Fragment shader ---
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";
*/

//----------------------------------------------- Shader end

int main()
{
    //----------------------------------------------------------------------------------------
    //
    // SET SETTINGS
    //
    //----------------------------------------------------------------------------------------

    // ---------------------------------------------------------------------------------------
    // GLFW: INITIALIZE AND CONFIGURE 
    // ---------------------------------------------------------------------------------------
    // GLFW s'occupe des fenetres open gl
    glfwInit(); // 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Max OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Min OpenGl Version
    //Specifie que l'on selectionne la version core pour avoir plus feature de OpenGl, sans prendre
    //En compte la retrocompatibilité
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //nb: Pour mac il faut ajouter cette ligne de code
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 


    // ---------------------------------------------------------------------------------------
    // GLFW : WINDOW CREATION     
    // ---------------------------------------------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    // si la fenetre ne fonctionne pas 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Attache le processus à la fenetre
    glfwMakeContextCurrent(window);
    // Fonctions qui va retourner le resize d'une fenetre
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //----------------------------------------
    // GLAD: load all OpenGL function pointers
    // ---------------------------------------
    // Permet de gerer les pointeurs opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // ---------------------------------------- End setings



    // --------------------------------------------------------------
    //
    // SHADER FROM Main 
    //
    // --------------------------------------------------------------
    // Cette partie ca compiler nos shaders avant de l'envoyer dans notre fenetre

    /*
    //----------------------------------------
    // Vertex shader
    // ---------------------------------------
    int vertexShader = glCreateShader(GL_VERTEX_SHADER); // ici je créé un vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // je lui assigne ma variable
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    // le & passe le int non pas en copie mais avec son adresse
    // ce qui va changer la variable sucess partout
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //----------------------------------------
    // Fragment shader
    // ---------------------------------------
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    // la variable succes ayant déjà été créé pas besoin de la refaire
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //----------------------------------------
    // Link shader
    // ---------------------------------------
    // Ici on assemble le Vertex shader et le Fragment shader
    //pour en faire un shader complet
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // On clean la memoire pour ne garder que le shader compilé
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */
    // -------------------------------------------------------------- Shader main end


    // SHADER depuis nos fichiers
    // ------------------------------------
    Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

    //----------------------------------------
    // VERTEX DATA, BUFFFER, VTX ATTRIBUTES
    // ---------------------------------------

    // Voilà les position de nos vertex 
    float vertices[] = {
        //  Position ----------  COLOR -----------
             0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
            -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,// top left 
    };

    // Les indices vont dire comment dessiner nos triangles.
    // pour faire un rectangle il faut reprendre les vertex precédent.
    // au lieux de refaire plusieurs fois les meme vertex, on indique
    // quels triangles dessiner 

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,  // first Triangle
        2, 3, 0   // second Triangle
    };
    unsigned int VBO, VAO, EBO;

    //Vertex array object
    // Va gerer les vertex dans le VBO
    // Attache le tableau de vertex en premier puis, attache et parramettre les vertex buffers
    //
    // bind the Vertex Array Object first, then bind and set vertex buffer(s)
    //and then configure vertex attributes(s).
    glGenVertexArrays(1, &VAO);

    // vertex buffer objects
    // Va stocker les vertex dans le tanpon
    glGenBuffers(1, &VBO);

    // element buffer objects
    // Ce qui va lier nos vertex en index
    glGenBuffers(1, &EBO);

    // 1. Attache Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 2.a Lie les vertex par indices 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.

    // ------ BONUS ------------
    // Debug view --------------------
    // Vertex point---
    //glEnable(GL_PROGRAM_POINT_SIZE); // Active vertex size 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Active vertex point view


    // Wireframe mode ---
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // --------------------------------------------------------------
    //
    // RENDER LOOP
    //
    // --------------------------------------------------------------

    // Affiche des images en continu dans la fenetre tant que la variable glfwWindowShouldClose close est false
    while (!glfwWindowShouldClose(window))
    {
        // input ---------------------------------------
        // Retourne les actions de l'utilisateur
        processInput(window);


        //RENDU ----------------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // PARENTHESE SHADER ----------------------------------
        // ## UNIFORM SHADER ##

        // Nous allons changer le shader à chaque appel de cette passe de rendu, afin
        // Il faut activer le shader avant tout
        // Cela fait que le cpu envoie une info au gpu
        // Aussi un uniform est une valeur unique par shader 
        // Aussi si l'uniform n'est pas utilisé dans notre code GLSL alors le compilateur 
        // Va virer cette derniere (#Souviens toi Ratp)
        ourShader.use();
        glBindVertexArray(VAO);
        //GlUseProgram(ourShader);

        /*
        float timeValue = glfwGetTime(); // hop choppe le temps
            // Comme le sin va de -1 à 1 en le divisant par 2 on le réduit de -0.5 à 0.5 en ajoutant 0.5 on arrive de 0 a 1
        float greenValue = sin(timeValue) / 2.0f + 0.5f; // -1 / 2 => -0.5 + 0.5 = 0 --- 1/2 = 0.5 +0.5 = 1 --- 0/2 = 0 +0.5 = 0.5 --- 0.5/2
            // je prend la variable située dans mon vertex shader pour la changer
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            //J'assigne ma nouvelle couleur
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */


        // --------------------------------------- FIN SHADER
    // draw our first triangle
    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
        // ------------------------------------ RENDU FIN

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        // Interchange les pixel precédent et les nouveau pixel une fois l'image déssinée.
        glfwSwapBuffers(window);

        glfwPollEvents();// Check les events de l'utilisateur
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // Si on Quitte la boucle while, on passe ici qui va vider le tout 
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void render_vertex()
{

}