#ifndef SRC_OBJECTS_ELEMENTBUFFER_HPP
#define SRC_OBJECTS_ELEMENTBUFFER_HPP
#include <GL/glew.h>

class ElementArray {
public:
    ElementArray(const GLuint* data, GLuint size, bool deleteOnDestruct = true) : m_ID(0), m_DeleteOnDestruct(deleteOnDestruct) {
        // Create a new element buffer and put the data into it
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~ElementArray() {
        // Delete the element buffer
        if (m_DeleteOnDestruct) {
            glDeleteBuffers(1, &m_ID);
        }
    }

    void Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }

    void Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint m_ID;
    bool m_DeleteOnDestruct;
};

#endif /* SRC_OBJECTS_ELEMENTBUFFER_HPP */
