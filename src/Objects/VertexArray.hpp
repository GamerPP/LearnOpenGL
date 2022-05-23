#ifndef SRC_OBJECTS_VERTEXARRAY_HPP
#define SRC_OBJECTS_VERTEXARRAY_HPP
#include <GL/glew.h>

#include "VertexBuffer.hpp"

class VertexArray {
public:
    VertexArray(bool deleteOnDestruct = true) : m_ID(0), m_DeleteOnDestruct(deleteOnDestruct) {
        // Create a new vertex array
        glGenVertexArrays(1, &m_ID);
    }

    ~VertexArray() {
        // Delete the vertex array
        if (m_DeleteOnDestruct) {
            glDeleteVertexArrays(1, &m_ID);
        }
    }

    void AttachVertexBuffer(VertexBuffer& buffer, GLuint layout, GLsizeiptr size, GLenum type, GLuint stride, void* offset) {
        this->Bind(); buffer.Bind();
        glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        buffer.Unbind();
    }

    void Bind() {
        glBindVertexArray(m_ID);
    }

    void Unbind() {
        glBindVertexArray(0);
    }

    GLuint m_ID;
    bool m_DeleteOnDestruct;
};

#endif /* SRC_OBJECTS_VERTEXARRAY_HPP */
