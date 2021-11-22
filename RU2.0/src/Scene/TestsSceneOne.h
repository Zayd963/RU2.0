#pragma once
#include "Scene/Scene.h"
#include "core/Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core/Texture.h"
#include <memory>
#include "core/Renderer2D.h"
#include "core/Camera.h"


class TestsSceneOne : public Scene
{
public:
	TestsSceneOne();

	void Update(float deltaTime) override;
	void Render() override;
	void IMGUIRender() override;

	~TestsSceneOne() { Renderer2D::ShutDown(); };
	
private:
	std::unique_ptr<Texture> texture;
	std::unique_ptr<Texture> texture1;
	std::unique_ptr<Texture> texture2;
	std::unique_ptr<Camera> camera;


};

