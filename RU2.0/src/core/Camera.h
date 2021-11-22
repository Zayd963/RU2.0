#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera()
	{
		position = glm::vec3(-50, -50, 0);
		proj = glm::perspective(45.f, 4.f / 3.f, 0.f, 100.f);
		view = glm::translate(glm::mat4(1.0f), position);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -250));
		MVP = proj * view * model;
	}
	void Update(float deltaTime)
	{
		proj = glm::perspective(360.f, 4.f / 3.f, 0.f, 100.f);
		view = glm::translate(glm::mat4(1.0f), position);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -250));
		MVP = proj * view * model;
	}

	glm::mat4 GetMVP() { return MVP; }

	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;
	glm::vec3 position;
};

