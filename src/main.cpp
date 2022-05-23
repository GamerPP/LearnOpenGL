#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader/Shader.hpp"
#include "Objects/ElementArray.hpp"
#include "Objects/VertexBuffer.hpp"
#include "Objects/VertexArray.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

GLuint indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
}; 

int main() {
    // Initialize GLFW and exit if it fails
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Tell GLFW to use OpenGL 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Check if the system is Apple and if so, set the forward compatibility flag
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a window and exit if it fails
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW and exit if it fails
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // Set the viewport and framebuffer size callback
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Create the shader
    Shader shader("vertex.glsl", "fragment.glsl");

    // Create the vertex buffer and element buffer
    VertexBuffer vbo(vertices, sizeof(vertices));
    ElementArray ebo(indices, sizeof(indices));

    // Create and bind the vertex array
    VertexArray vao; vao.Bind();

    // Attach the vertex buffer to the vertex array
    vao.AttachVertexBuffer(vbo, 0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);

    // Unbind objects
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Set the clear color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Process input
        ProcessInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind shader and objects
        shader.Enable();
        vao.Bind();
        ebo.Bind();

        // Render
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Set the viewport to the new size of the window
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
    // Close the window if the ESC key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}