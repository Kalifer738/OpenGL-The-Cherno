#pragma once
#include <string>
#include <unordered_map>
#include <ext/matrix_float4x4.hpp>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RenderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

public:
	Shader(const std::string& shaderPath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//Set uniforms
	void SetUniform1i(const std::string name, int value);
	void SetUniform1f(const std::string name, float value);
	void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string name, const glm::mat4& matrix4);
};