#pragma once

#include <unordered_map>

#include "glm/glm.hpp"

using namespace std;

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};


class Shader
{
private:
	string m_FilePath;
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLocationCache;
public:
	Shader(const string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1i(const string& name, int value);
	void SetUniform1f(const string& name, float value);
	void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void SetUniformMath4f(const string& name, const glm::mat4& matrix);
private:
	ShaderProgramSource ParseShader(const string& filepath);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
	int GetUniformLocation(const string& name);
};