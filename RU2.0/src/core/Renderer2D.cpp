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

	data.shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
	data.ibo = std::make_unique<IndexBuffer>(indicies, data.maxIndicies);
	data.vao = std::make_unique<VertexArray>();
	data.vbo = std::make_unique<VertexBuffer>(sizeof(Vertex) * data.maxVerticies);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
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

void Renderer2D::DrawQuad(glm::vec3 _position, float size, float _texIndex)
{
	Vertex v0;
	v0.position = { _position.x, _position.y , 1.0f };
	v0.texCoord = { 0.f, 0.f };
	v0.texIndex = _texIndex;
	memcpy(renderData + offset, &v0, sizeof(v0));
	offset++;

	Vertex v1;
	v1.position = { _position.x + size, _position.y , 1.0f };
	v1.texCoord = { 1.f, 0.f };
	v1.texIndex = _texIndex;
	memcpy(renderData + offset, &v1, sizeof(v0));
	offset++;

	Vertex v2;
	v2.position = { _position.x + size, _position.y + size , 1.0f };
	v2.texCoord = { 1.f, 1.f };
	v2.texIndex = _texIndex;
	memcpy(renderData + offset, &v2, sizeof(v0));
	offset++;

	Vertex v3;
	v3.position = { _position.x, _position.y + size , 1.0f };
	v3.texCoord = { 0.f, 1.f };
	v3.texIndex = _texIndex;
	memcpy(renderData + offset, &v3, sizeof(v0));
	offset++;
}

void Renderer2D::End()
{
	data.vbo->SetData(renderData, sizeof(Vertex) * data.maxVerticies);
	Flush();
}

void Renderer2D::Flush()
{
	GLCall(glDrawElements(GL_TRIANGLES, data.ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::StartBatch()
{
	offset = 0;
}
