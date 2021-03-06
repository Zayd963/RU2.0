#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec4 color;
	
	float texIndex;
};

struct RenderData
{
	const unsigned int maxQuads = 128;
	const unsigned int maxVerticies = maxQuads * 4;
	const unsigned int maxIndicies = maxQuads * 6;

	std::unique_ptr<Texture> whiteTexture;

	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<IndexBuffer> ibo;
	std::unique_ptr<Shader> shader;

	glm::vec4 quadPositions[4];
};

class Renderer2D
{
public:
	static void Init();
	static void Begin(Camera &camera);
	static void DrawQuad(glm::vec3 position,float size, float texIndex, float angle = 0.0f, glm::vec4 color = glm::vec4(1.0f));
	static void DrawQuad(glm::vec3 position,float size, glm::vec4 color, float angle = 0.0f);
	static void End();
	static void ShutDown();
private:
	static void Flush();
	static void StartBatch();
	static unsigned int offset;
};

