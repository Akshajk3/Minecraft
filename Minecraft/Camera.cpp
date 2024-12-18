#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::CamMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader)
{
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, up);
    glm::mat4 proj = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
}


void Camera::PosMatrix(Shader& shader)
{
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, up);
    glm::vec3 eyePos = glm::vec3(glm::inverse(view) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // Calculate camera position in eye space

    glUniform3fv(glGetUniformLocation(shader.ID, "cameraPos"), 1, glm::value_ptr(eyePos)); // Pass camera position to the shader
}

void Camera::MoveCamera(GLFWwindow* window)
{
    if (captured)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height * deltaTime;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width * deltaTime;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, up)));

        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), up);

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        CaptureMouse(window);
    }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        ReleaseMouse(window);
    }
}

void Camera::CaptureMouse(GLFWwindow* window)
{
    if (firstClick && captured == false)
    {
        glfwSetCursorPos(window, (width / 2), (height / 2));
        firstClick = false;
        captured = true;
    }
}

void Camera::ReleaseMouse(GLFWwindow* window)
{
    if (captured == true)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
        captured = false;
    }
}

void Camera::UpdateDeltaTime(float DeltaTime)
{
    deltaTime = DeltaTime;
}

// void Camera::UpdateAABB()
// {
//     float playerWidth = 0.5f;
//     float playerHeight = 1.8f;
//     float playerDepth = 0.5f;

//     aabb.min = Position - glm::vec3(playerWidth, playerHeight, playerDepth);
//     aabb.max = Position + glm::vec3(playerWidth, playerHeight, playerDepth);
// }