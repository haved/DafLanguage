#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();
	bool LoadShaders(const std::string& vertexShader, const std::string& fragmentShader);
	void UnloadShader();
	GLuint GetUniformLocation(const std::string& name);
	inline void Bind() {
        glUseProgram(m_programID);
	}
private:
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
    bool loaded;
    GLuint m_programID;
};
