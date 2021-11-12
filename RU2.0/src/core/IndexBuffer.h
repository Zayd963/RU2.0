#pragma once
class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int _count);
	void Bind() const;
	void UnBind() const;
	~IndexBuffer();

	inline unsigned int GetCount() const { return count; }
};