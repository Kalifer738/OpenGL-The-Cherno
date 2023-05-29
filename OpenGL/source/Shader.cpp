#pragma once
#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <fstream> //TODO: "use C streams, they tend to be faster": The Cherno
#include <string>


Shader::Shader(const std::string& shaderPath) : m_FilePath(shaderPath), m_RenderID(0) {
	ShaderProgramSource source = ParseShader(m_FilePath);
	m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RenderID));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4& matrix4) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix4[0][0]));
	
}


void Shader::SetUniform1f(const std::string name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value))
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		// Allocate the message on the stack
		char* message = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream  stream(filepath);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

int Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];  
	}

	GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
	if (location == -1) {
		std::cout << "Warrning: uniform: " << name << " does't exist!" << std::endl;
	}

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::Bind() const {
	GLCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const {
	GLCall(glUseProgram(0));
}
