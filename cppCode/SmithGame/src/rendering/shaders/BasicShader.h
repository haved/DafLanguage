#pragma once

#include "../Shader.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

class BasicShader {
    public:
        BasicShader(const std::string& vertexShader, const std::string& fragmentShader);
        void LoadToGPU();
        void UnloadFromGPU();
        inline void SetModelspaceMatrix(const glm::mat4& modelspace) {
            glUniformMatrix4fv(m_modelspaceMatrix_id, 1, GL_FALSE, &modelspace[0][0]);
        }
        inline void SetMVP(const glm::mat4& MVP) {
            glUniformMatrix4fv(m_MVP_id, 1, GL_FALSE, &MVP[0][0]);
        }
        inline void SetColor(const glm::vec4& color) {
            glUniform4f(m_color_id, color.x, color.y, color.z, color.w);
        }
        inline void Bind() {
            m_shader.Bind();
        }
    private:
        std::string m_vertexShader;
        std::string m_fragmentShader;
        Shader m_shader;
        GLuint m_modelspaceMatrix_id;
        GLuint m_MVP_id;
        GLuint m_color_id;
};
