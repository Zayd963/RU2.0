#pragma once
class VertexBuffer
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(unsigned int size);
	void Bind() const;
	void SetData(const void* data, const unsigned int size);
	void UnBind() const;
	~VertexBuffer();
};