#include "Texture.hpp"

Texture::Texture(const std::string name, GLenum texType, GLenum slot) {
	m_Type = texType;

    int width, height;
	unsigned char* bytes = SOIL_load_image(("Resources/Textures/" + name).c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0 + slot);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Bind() {
	glBindTexture(m_Type, m_ID);
}

void Texture::Unbind() {
	glBindTexture(m_Type, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_Type);
}