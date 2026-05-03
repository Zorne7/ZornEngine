#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "math.h"

class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetMat4(const std::string& name, const Math::Mat4& matrix) const;
    void SetFloat3(const std::string& name, const Math::Vec3& value) const;

private:
    unsigned int CompileShader(unsigned int type, const std::string& source) const;
    unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource) const;
    int GetUniformLocation(const std::string& name) const;

private:
    unsigned int m_RendererID = 0;
};

#endif // SHADER_H
