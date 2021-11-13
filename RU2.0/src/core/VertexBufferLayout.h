#pragma once
#include <vector>

#include <GL/glew.h>

#include "Debug.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char isNormalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_INT: return 4;
		}
		
		ASSERT(false);
		return 0;
	}
	
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout()
		:stride(0)
	{

	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<int>(unsigned int count)
	{
		elements.push_back({ GL_INT, count, GL_FALSE });
		stride += VertexBufferElement::GetSizeOfType(GL_INT) * count;
	}

	inline std::vector<VertexBufferElement> GetElements() const& { return  elements; }
	inline unsigned int GetStride() const { return stride; }

	~VertexBufferLayout() {}
};

