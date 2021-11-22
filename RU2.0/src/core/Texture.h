#pragma once

#include "Debug.h"
#include "Renderer.h"

class Texture
{
private:
	unsigned int rendererID;
	std::string filepath;
	unsigned char* localBuffer;
	int width;
	int height;
	int BPP;
public:
	Texture(const std::string& _filepath);
	Texture(const unsigned int _height, const unsigned int _width);

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	void SetData(const void* data);

	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }

	~Texture();
};

