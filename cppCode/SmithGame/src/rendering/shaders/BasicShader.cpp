#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexShader, const std::string& fragmentShader) : m_vertexShader(vertexShader), m_fragmentShader(fragmentShader) {}

void BasicShader::LoadToGPU() {
    if(m_shader.LoadShaders(m_vertexShader, m_fragmentShader)) {
        m_modelspaceMatrix_id = m_shader.GetUniformLocation("modelspaceMatrix");
        m_MVP_id = m_shader.GetUniformLocation("MVP");
        m_color_id = m_shader.GetUniformLocation("color");
    }
}

inline void BasicShader::UnloadFromGPU() {
    m_shader.UnloadShader();
}
