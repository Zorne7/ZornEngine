#include "shader.h"
#include <glad/glad.h>
#include <iostream>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
    m_RendererID = CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
    if (m_RendererID != 0) {
        glDeleteProgram(m_RendererID);
    }
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, ' ');
        glGetShaderInfoLog(id, length, &length, &message[0]);
        std::cerr << "Shader compilation error: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) const
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (vs == 0 || fs == 0) {
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, ' ');
        glGetProgramInfoLog(program, length, &length, &message[0]);
        std::cerr << "Shader link error: " << message << std::endl;
        glDeleteProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return 0;
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::GetUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(m_RendererID, name.c_str());
}

void Shader::SetMat4(const std::string& name, const Math::Mat4& matrix) const
{
    int location = GetUniformLocation(name);
    if (location == -1)
        return;
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
}

void Shader::SetFloat3(const std::string& name, const Math::Vec3& value) const
{
    int location = GetUniformLocation(name);
    if (location == -1)
        return;
    glUniform3f(location, value.x, value.y, value.z);
}
