#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

class Player
{
public:
    Player(Camera* camera);

    void SetCameraFocus(bool focus, GLFWwindow* window);

private:
    Camera* camera;
};