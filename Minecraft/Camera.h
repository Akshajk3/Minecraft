#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"
#include "AABB.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;
	bool captured = false;

	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	float deltaTime = 0.0f;

	Camera(int width, int height, glm::vec3 position);

	void CamMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader);
	void PosMatrix(Shader& shader);
	void Inputs(GLFWwindow* window);

	void CaptureMouse(GLFWwindow* window);
	void ReleaseMouse(GLFWwindow* window);
	void UpdateDeltaTime(float deltaTime);
	void UpdateAABB();

	//AABB aabb;
};