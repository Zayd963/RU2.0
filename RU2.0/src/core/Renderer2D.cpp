#include "Renderer2D.h"

Vertex renderData[512];
unsigned int Renderer2D::offset = 0;

static RenderData data;

void Renderer2D::Init()
{
	unsigned int indicies[128 * 6];
	unsigned int indexOffset = 0;
	for (uint32_t i = 0; i < data.maxIndicies; i += 6)
	{
		indicies[i + 0] = indexOffset + 0;
		indicies[i + 1] = indexOffset + 1;
		indicies[i + 2] = indexOffset + 2;
						  
		indicies[i + 3] = indexOffset + 2;
		indicies[i + 4] = indexOffset + 3;
		indicies[i + 5] = indexOffset + 0;

		indexOffset += 4;
	}

	data.quadPositions[0] = { -0.5f, -0.5f, 0.f, 1.f };
	data.quadPositions[1] = { 0.5f, -0.5f, 0.f, 1.f };
	data.quadPositions[2] = { 0.5f, 0.5f, 0.f, 1.f };
	data.quadPositions[3] = { -0.5f, 0.5f, 0.f, 1.f };

	data.shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
	data.ibo = std::make_unique<IndexBuffer>(indicies, data.maxIndicies);
	data.vao = std::make_unique<VertexArray>();
	data.vbo = std::make_unique<VertexBuffer>(sizeof(Vertex) * data.maxVerticies);

	data.whiteTexture = std::make_unique<Texture>(1, 1);
	uint32_t texData = 0xffffffff;

	data.whiteTexture->SetData(&texData);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(4);
	layout.Push<float>(1);
	data.vao->AddBuffer(*data.vbo, layout);

	int samplers[32];
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}
	data.shader->Bind();
	data.ibo->Bind();
	data.vao->Bind();
	data.vbo->Bind();
	data.shader->SetUniform1iv("u_Texture", samplers, 32);
	
	
}

void Renderer2D::Begin(Camera& camera)
{
	data.shader->SetUniformMat4f("u_MVP", camera.MVP);
	StartBatch();
}

void Renderer2D::DrawQuad(glm::vec3 _position, float size, float _texIndex, float angle, glm::vec4 color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.f, 0.f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { size, size, 1.0f });

	Vertex v0;
	v0.position = transform * data.quadPositions[0];
	v0.texCoord = { 0.f, 0.f };
	v0.texIndex = _texIndex;
	v0.color = color;
	memcpy(renderData + offset, &v0, sizeof(v0));
	offset++;

	Vertex v1;
	v1.position = transform * data.quadPositions[1];
	v1.texCoord = { 1.f, 0.f };
	v1.texIndex = _texIndex;
	v1.color = color;
	memcpy(renderData + offset, &v1, sizeof(v0));
	offset++;

	Vertex v2;
	v2.position = transform * data.quadPositions[2];
	v2.texCoord = { 1.f, 1.f };
	v2.texIndex = _texIndex;
	v2.color = color;
	memcpy(renderData + offset, &v2, sizeof(v0));
	offset++;

	Vertex v3;
	v3.position = transform * data.quadPositions[3];
	v3.texCoord = { 0.f, 1.f };
	v3.texIndex = _texIndex;
	v3.color = color;
	memcpy(renderData + offset, &v3, sizeof(v0));
	offset++;
}

void Renderer2D::DrawQuad(glm::vec3 _position, float size, glm::vec4 color, float angle)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.f, 0.f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { size, size, 1.0f });

	Vertex v0;
	v0.position = transform * data.quadPositions[0];
	v0.texCoord = { 0.f, 0.f };
	v0.texIndex = 0;
	v0.color = color;
	memcpy(renderData + offset, &v0, sizeof(v0));
	offset++;

	Vertex v1;
	v1.position = transform * data.quadPositions[1];
	v1.texCoord = { 1.f, 0.f };
	v1.texIndex = 0;
	v1.color = color;
	memcpy(renderData + offset, &v1, sizeof(v0));
	offset++;

	Vertex v2;
	v2.position = transform * data.quadPositions[2];
	v2.texCoord = { 1.f, 1.f };
	v2.texIndex = 0;
	v2.color = color;
	memcpy(renderData + offset, &v2, sizeof(v0));
	offset++;

	Vertex v3;
	v3.position = transform * data.quadPositions[3];
	v3.texCoord = { 0.f, 1.f };
	v3.texIndex = 0;
	v3.color = color;
	memcpy(renderData + offset, &v3, sizeof(v0));
	offset++;
}

void Renderer2D::End()
{
	data.vbo->SetData(renderData, sizeof(Vertex) * data.maxVerticies);
	Flush();
}

void Renderer2D::ShutDown()
{
	
}

void Renderer2D::Flush()
{
	GLCall(glDrawElements(GL_TRIANGLES, data.ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::StartBatch()
{
	offset = 0;
}
