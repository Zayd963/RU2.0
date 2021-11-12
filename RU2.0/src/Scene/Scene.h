#pragma once
class Scene
{
public:
	Scene() {};

	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void IMGUIRender() {};

	~Scene() {};

};

