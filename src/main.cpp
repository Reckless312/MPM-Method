#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Program/Program.h"
#include "Exceptions/ProgramException.h"
#include "Exceptions/ShaderException.h"
#include "Exceptions/TextureException.h"
#include "Shaders/Shader.h"
#include "TextureLoader/TextureLoader.h"

int main() {
    Program::InitializeGLFW();

    try {
        Program::CreateWindowAndAssignContext();
        Program::LoadGladLibrary();
    } catch (const ProgramException& exception) {
        return Program::ReportErrorAndTerminate(exception.what());
    }

    Program::SetViewportAndResizerCallback();

    const char* vertexShader = "vertexShader.vs";
    const char* fragmentShader = "fragmentShader.fs";

    const Shader shaderProgram(vertexShader, fragmentShader);

    try {
        shaderProgram.Load();
    } catch (const ShaderException& exception) {
        return Program::ReportErrorAndTerminate(exception.what());
    }

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
   };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    constexpr int bufferObjectsCount = 1;

    unsigned int VAO, VBO, EBO;

    glGenBuffers(bufferObjectsCount, &VBO);
    glGenBuffers(bufferObjectsCount, &EBO);
    glGenVertexArrays(bufferObjectsCount, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    TextureLoader textureLoader("peak.jpg");

    try {
        textureLoader.Load();
    } catch (const TextureException& exception) {
        return Program::ReportErrorAndTerminate(exception.what());
    }

    while (!glfwWindowShouldClose(Program::window))
    {
        Program::ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        textureLoader.Bind(GL_TEXTURE0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(Program::window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
