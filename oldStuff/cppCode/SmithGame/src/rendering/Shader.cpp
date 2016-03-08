
#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader() :loaded(false) {}

Shader::~Shader()
{
	std::cout << "~Shader()" << std::endl;
	if(loaded)
        glDeleteProgram(m_programID);
}

bool Shader::LoadShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    if(loaded)
        return false;
	m_programID = glCreateProgram();
	loaded=true;
	GLuint vertexShaderID = CreateShader(LoadShader(vertexShader), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = CreateShader(LoadShader(fragmentShader), GL_FRAGMENT_SHADER);

	glAttachShader(m_programID, vertexShaderID);
	glAttachShader(m_programID, fragmentShaderID);

	glLinkProgram(m_programID);
	CheckShaderError(m_programID, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_programID);
	CheckShaderError(m_programID, GL_LINK_STATUS, true, "Invalid shader program");

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return true;
}

void Shader::UnloadShader() {
    if(!loaded)
        return;
    glDeleteProgram(m_programID);
    loaded = false;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		char c[2];
		c[1] = '\0';
		while (file.get(c[0]))
		{
			output.append(c);
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, type==GL_VERTEX_SHADER?"Error compiling vertex shader!":"Error compiling fragment shader!");

	return shader;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::GetUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_programID, name.c_str());
}
