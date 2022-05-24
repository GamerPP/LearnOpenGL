#ifndef SRC_TEXTURE_TEXTURE_HPP
#define SRC_TEXTURE_TEXTURE_HPP
#include <string>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

class Texture {
public:
	Texture(const std::string name, GLenum texType, GLenum slot);
    ~Texture();

	void Bind();
	void Unbind();
    
    GLuint m_ID;
	GLenum m_Type;
};

#endif /* SRC_TEXTURE_TEXTURE_HPP */
