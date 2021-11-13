#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include "Debug.h"
#include "Renderer.h"



Shader::Shader(const std::string& _filepath)
	:filepath(_filepath), rendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

void Shader::Bind() const
{
    GLCall(glUseProgram(rendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const std::string& name, int value[], const int& count)
{
    GLCall(glUniform1iv(GetUniformLocation(name), count, value));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& value)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));
    if (location == -1)
        std::cout << "Uniform: " << name << " not found" << std::endl;
    else
        uniformLocationCache[name] = location;
   
    return location;
}

unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed To Compile: " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    std::string line;
    std::stringstream ss[2];
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment"))
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            {
                ss[(int)type] << line << "\n";
            }
        }
    }

    return { ss[0].str(), ss[1].str() };

}
