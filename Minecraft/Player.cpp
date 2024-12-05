#include "Player.h"

Player::Player(Camera* pCamera)
    : camera(pCamera)
{
    position = camera->Position;
    size = glm::vec3(0.3f, 0.9f, 0.3f);
}

void Player::SetCameraFocus(bool focus, GLFWwindow* window)
{
    if (focus)
    {
        camera->CaptureMouse(window);
    }
    else
    {
        camera->ReleaseMouse(window);
    }
}

bool Player::CanMove(const glm::vec3& targetPosition, const std::vector<AABB>& worldBounds)
{
    glm::vec3 direction = targetPosition - position;
    float stepSize = 0.1f;  // Small step size for collision checking
    glm::vec3 step = glm::normalize(direction) * stepSize;
    glm::vec3 currentPos = position;

    while (glm::length(currentPos - targetPosition) > stepSize)
    {
        currentPos += step;

        AABB playerAABB{
            currentPos - size,
            currentPos + size
        };

        for (const auto& bound : worldBounds)
        {
            if (playerAABB.Intersects(bound))
            {
                return false; // Collision detected, can't move
            }
        }
    }
    
    return true; // No collisions, can move
}

void Player::HandleMovement(GLFWwindow* window, Shader& shaderProgram, const std::vector<AABB>& worldBounds)
{
    glm::vec3 forward = camera->Orientation;
    glm::vec3 up = camera->up;
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    glm::vec3 movement(0.0f);

    // Horizontal Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement += speed * forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement += speed * -right;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement += speed * -forward;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement += speed * right;
    
    // Vertical Movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movement += speed * up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movement += speed * -up;

    // Normalize Movement
    if (glm::length(movement) > 0.0f)
        glm::normalize(movement);

    // Sprinting
    speed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 0.2f : 0.1f;

    glm::vec3 targetPosition = camera->Position + movement;
    position = targetPosition;
    camera->Position = position;
    camera->PosMatrix(shaderProgram);
    
    // Change Render Mode
    static bool renderModeLine = false;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !renderModeLine)
    {
        renderModeLine = true;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && renderModeLine)
    {
        renderModeLine = false;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    camera->MoveCamera(window);
}

void Player::Update(Shader& shaderProgram, GLFWwindow* window, const std::vector<AABB>& worldBounds)
{
    HandleMovement(window, shaderProgram, worldBounds);
    camera->CamMatrix(45.0f, 0.1f, 60.0f, shaderProgram);
}