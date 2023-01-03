#include "Shader.h"
#include <fstream>
#include <iostream>

#include "Debug.h"

using namespace Resource;

int createCompileShader(const char* fileName, GLenum type)
{
	std::ifstream file;
	std::string shader;

	char line[256];

	file.open(fileName, std::ios::in | std::ios::ate);

	if (!file.is_open())
	{
		std::cout << "Shader can't be openned : " << fileName;
		return 0;
	}
	file.seekg(0);

	while (file.getline(line, 256))
	{
		shader.push_back('\n');
		for (int i = 0; line[i] != '\0'; i++)
			shader.push_back(line[i]);
	}
	shader.push_back('\0');

	const char* shaderChar = shader.c_str();
	int id = glCreateShader(type);
	glShaderSource(id, 1, &shaderChar, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		Core::Debug::log.Print("ERROR::SHADER::COMPILATION_FAILED : %s\n %s\n", fileName, infoLog);
		ASSERT(0, "Compilation failed");
	}

	std::cout << "Shader loaded : " << fileName << std::endl;
	return id;
}

void Shader::createShader(const char* vertexShader, const char* fragmentShader)
{
	int vertexId = createCompileShader(vertexShader, GL_VERTEX_SHADER);
	int fragmentId = createCompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(shaderProgram, vertexId);
	glAttachShader(shaderProgram, fragmentId);

	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Core::Debug::log.Print("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", infoLog);
		ASSERT(0, "Linking failed");
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::Load(const char* name)
{
	
}

void Shader::Unload()
{
	glDeleteProgram(shaderProgram);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const myMaths::Float2& value) const
{
	glUseProgram(shaderProgram);
	glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value.x);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUseProgram(shaderProgram);
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const myMaths::Float3& value) const
{
	glUseProgram(shaderProgram);
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value.x);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUseProgram(shaderProgram);
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const myMaths::Float4& value) const
{
	glUseProgram(shaderProgram);
	glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value.x);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	glUseProgram(shaderProgram);
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

void Shader::setMat4(const std::string& name, const myMaths::Mat4& mat) const
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_TRUE, &mat.mat[0][0]);
}

void Shader::setMat4(const std::string& name, const myMaths::Mat4& mat, bool transposed) const
{
	glUseProgram(shaderProgram);

	//Core::Debug::log.Print("%s : %d", name.c_str(), glGetUniformLocation(shaderProgram, name.c_str()));

	if (transposed)
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat.mat[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_TRUE, &mat.mat[0][0]);
}