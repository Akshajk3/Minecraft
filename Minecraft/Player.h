#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "AABB.h"
#include "Shader.h"

class Player
{
public:
    Player(Camera* camera);

    void SetCameraFocus(bool focus, GLFWwindow* window);

    glm::vec3 GetMin() const { return position; }
    glm::vec3 GetMax() const { return position + size; }
    void HandleMovement(GLFWwindow* window, Shader& shaderProgram, const std::vector<AABB>& worldBounds);
    bool CanMove(const glm::vec3& delta, const std::vector<AABB>& worldBounds);
    void Update(Shader& shaderProgram, GLFWwindow* window, const std::vector<AABB>& worldBounds);

private:
    Camera* camera;
    glm::vec3 position;
    glm::vec3 size;
    float speed = 0.1f;
};