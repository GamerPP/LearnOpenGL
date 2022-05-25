#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>

#include "Shader/Shader.hpp"
#include "Objects/ElementArray.hpp"
#include "Objects/VertexBuffer.hpp"
#include "Objects/VertexArray.hpp"
#include "Texture/Texture.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

GLfloat vertices[] = {
    // Positions         // Colors          // Texture Coords
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // Top Right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f // Top Left 
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
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
    vao.AttachVertexBuffer(vbo, 0, 3, GL_FLOAT, sizeof(GLfloat) * 8, (GLvoid*)0);
    vao.AttachVertexBuffer(vbo, 1, 3, GL_FLOAT, sizeof(GLfloat) * 8, (GLvoid*)(3 * sizeof(GLfloat)));
    vao.AttachVertexBuffer(vbo, 2, 2, GL_FLOAT, sizeof(GLfloat) * 8, (GLvoid*)(6 * sizeof(GLfloat)));

    // Unbind objects
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    shader.Disable();

    // Create the textures
    Texture texture1("container.jpg", GL_TEXTURE_2D, 0);
    Texture texture2("awesomeface.png", GL_TEXTURE_2D, 1);

    // Set the shader's texture samplers
    shader.Enable();
    glUniform1i(shader.GetUniformLocation("uTexture1"), 0);
    glUniform1i(shader.GetUniformLocation("uTexture2"), 1);
    shader.Disable();


    // Set the clear color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Process input
        ProcessInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind shader, texture, and objects
        shader.Enable();
        vao.Bind();
        ebo.Bind();
    
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans,glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(shader.GetUniformLocation("transform"), 1, GL_FALSE, glm::value_ptr(trans));

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