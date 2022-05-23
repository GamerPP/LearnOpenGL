#ifndef SRC_SHADER_SHADER_HPP
#define SRC_SHADER_SHADER_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>

class Shader {
private:
    mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
    Shader(const std::string vertexPath, const std::string fragmentPath, bool deleteOnDestruct = true);
    ~Shader();

    GLint GetUniformLocation(const std::string& name) const;
    void Enable();

    unsigned int m_ID;
    bool m_DeleteOnDestruct;
};

#endif /* SRC_SHADER_SHADER_HPP */
