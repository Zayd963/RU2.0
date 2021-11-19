#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& _filepath);

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1fv(const std::string& name, float value[], int count);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1iv(const std::string& name, int value[], const int &count);
	void SetUniformMat4f(const std::string& name, glm::mat4& value);
	~Shader();

private:
	unsigned int rendererID;
	std::string filepath;

	std::unordered_map<std::string, int> uniformLocationCache;

	unsigned int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);

};

