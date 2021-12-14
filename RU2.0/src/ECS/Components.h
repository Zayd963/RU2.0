#pragma once
#include "glm/glm.hpp"
struct TransformComponent
{
	glm::mat4 transform;

	TransformComponent() = default;
	TransformComponent(const glm::mat4& other) : transform(other) {};
};