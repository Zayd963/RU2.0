#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera();
	
	void Update(float deltaTime);

	inline glm::mat4 GetMVP() const { return MVP; }

	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;
	glm::vec3 position;

	glm::vec3 startPan = { 0, 0, 0 };
	glm::vec2 endPan;

	float cameraSpeed;
};

