#include "Shader.hpp"

Shader::Shader(const std::string vertexPath, const std::string fragmentPath, bool deleteOnDestruct) : m_ID(0), m_DeleteOnDestruct(deleteOnDestruct) {
    // Create file streams to read the vertex and fragment shader files
    std::ifstream vertexFile("Resources/Shaders/" + vertexPath);
    std::ifstream fragmentFile("Resources/Shaders/" + fragmentPath);

    // Check if the files were opened successfully
    if (!vertexFile.is_open()) {
        std::cout << "Failed to open vertex shader file: " << vertexPath << std::endl;
        return;
    } if (!fragmentFile.is_open()) {
        std::cout << "Failed to open fragment shader file: " << fragmentPath << std::endl;
        return;
    }

    // Read the vertex and fragment shader source code into string streams
    std::stringstream vertexStream, fragmentStream;
    std::string line;
    while (getline(vertexFile, line)) vertexStream << line << "\n";
    while (getline(fragmentFile, line)) fragmentStream << line << "\n";

    // Close the file streams
    vertexFile.close();
    fragmentFile.close();

    // Convert the string streams into strings
    std::string vertexSource = vertexStream.str();
    std::string fragmentSource = fragmentStream.str();

    // Convert the strings into char arrays
    const char* vertexSourceChar = vertexSource.c_str();
    const char* fragmentSourceChar = fragmentSource.c_str();

    // Create a vertex shader and compile it
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSourceChar, NULL);
    glCompileShader(vertex);

    // Check if the vertex shader compiled successfully
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Failed to compile vertex shader: " << infoLog << std::endl;
        return;
    } std::cout << "Successfully compiled vertex shader.\n";

    // Create a fragment shader and compile it
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSourceChar, NULL);
    glCompileShader(fragment);

    // Check if the fragment shader compiled successfully
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "Failed to compile fragment shader: " << infoLog << std::endl;
        return;
    } std::cout << "Successfully compiled fragment shader.\n";

    // Create a shader program and attach the vertex and fragment shaders
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);

    // Link the shader program
    glLinkProgram(m_ID);

    // Check if the shader program linked successfully
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "Failed to link shader program: " << infoLog << std::endl;
        return;
    } std::cout << "Successfully linked shader program.\n";

    // Delete the shaders as they are no longer needed
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Enable the shader program
    glUseProgram(m_ID);
};

Shader::~Shader() {
    if (m_DeleteOnDestruct)
        glDeleteProgram(m_ID);
};

GLint Shader::GetUniformLocation(const std::string& name) const {
    auto locationSearch = m_UniformLocationCache.find(name);
    if (locationSearch != m_UniformLocationCache.end())
        return locationSearch->second;

    GLint location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1) {
        std::cout << "Could not find uniform: \"" << name << "\"\n";
        return -1;
    }
    m_UniformLocationCache[name] = location;

    return location;
}

void Shader::Enable() {
    glUseProgram(m_ID);
};

void Shader::Disable() {
    glUseProgram(0);
};
