#pragma once
#include "Scene/Scene.h"
#include "core/Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core/Texture.h"
#include <memory>
class TestsSceneOne : public Scene
{
public:
	TestsSceneOne();

	void Update(float deltaTime) override;
	void Render() override;
	void IMGUIRender() override;

	~TestsSceneOne() {};

private:
	glm::vec3 translationa;
	glm::vec3 translationb;
	glm::mat4 proj;
	glm::mat4 view;
	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<IndexBuffer> ibo;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<Texture> texture1;
	std::unique_ptr<Texture> texture2;
};

