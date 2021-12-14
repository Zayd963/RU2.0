#include "Camera.h"
#include "Input.h"
Camera::Camera()
	:cameraSpeed(100)
{
	position = glm::vec3(0, 0, -250);
	proj = glm::perspective(45.f, 4.f / 3.f, 0.f, 100.f);
	view = glm::translate(glm::mat4(1.0f), position);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -250));
	MVP = proj * view * model;
}

void Camera::Update(float deltaTime)
{
	glm::vec3 mousePos = { (float)Input::GetMouseX(), (float)Input::GetMouseY(), 0 };

	if (Input::isMouseDown(SDL_BUTTON_RMASK))
	{
		startPan = mousePos;
	}

	if (Input::isMouseHeld(SDL_BUTTON_RMASK))
	{
		position.x += mousePos.x - startPan.x;
		position.y -= mousePos.y - startPan.y;
		startPan = mousePos;
	}

	proj = glm::perspective(360.f, 4.f / 3.f, 0.f, 100.f);
	view = glm::translate(glm::mat4(1.0f), position);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	MVP = proj * view * model;
}
