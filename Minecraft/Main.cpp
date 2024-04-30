#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "World.h"
#include "Tree.h"

const unsigned int width = 1280;
const unsigned int height = 720;
glm::vec3 SkyColor(0.007f, 0.8f, 0.996f);
glm::vec3 StartingPos(0.0f, 20.0f, 0.0f);

Camera camera(width, height, StartingPos);

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void resizeWindowCallback(GLFWwindow* window, int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
}

void windowFocusCallback(GLFWwindow* window, int focused)
{
    if (focused)
    {
        camera.CaptureMouse(window);
    }
    else
    {
        camera.ReleaseMouse(window);
    }
}

int main()
{
    glfwSetErrorCallback(errorCallback);
    
    if(!glfwInit())
    {
        std::cout << "Failed to Init GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Vindelcraft", NULL, NULL);

    if (window == nullptr)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, resizeWindowCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);

    glfwMakeContextCurrent(window);

    gladLoadGL();
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    int frameWidth, frameHeight;
    
    glfwGetWindowSize(window, &frameWidth, &frameHeight);

    glViewport(0, 0, width, height);

    glm::vec3 fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
    float fogStart = 10.0f;
    float fogEnd = 50.0f;
    float fogDensity = 0.02f;

    Shader shaderProgram("vert.glsl", "frag.glsl");

    glEnable(GL_DEPTH_TEST);

    World world(8, 512);

    camera.Position = glm::vec3(world.GetSize() / 2 * CHUNK_WIDTH, StartingPos.y, world.GetSize() / 2 * CHUNK_LENGTH);
    
    glfwSetWindowSize(window, width + 1, height + 1);
    glfwSetWindowSize(window, width, height);

    // glfwSwapInterval is used to turn on and off Vsync
    // 0 = off, 1 = on
    glfwSwapInterval(1);
    
    double lastTime = glfwGetTime();
    int frame = 0;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(SkyColor.x, SkyColor.y, SkyColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Inputs(window);
        camera.CamMatrix(45.0f, 0.1f, 60.0f, shaderProgram);
        camera.PosMatrix(shaderProgram);

        //grassTex.Bind();

        world.ManageChunks(glm::vec2(camera.Position.x, camera.Position.z));
        world.DrawChunks();
        
        //block.Draw();

        double currentTime = glfwGetTime();
        frame++;

        float deltaTime = 1.0f;
        //std::cout << deltaTime << std::endl;
        camera.UpdateDeltaTime(deltaTime);

        if (currentTime - lastTime >= 1)
        {
            char title[255];
            snprintf(title, sizeof(title), "Vindelcraft: FPS: %i", frame);
            glfwSetWindowTitle(window, title);
            frame = 0;
            lastTime = currentTime;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
