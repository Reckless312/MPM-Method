#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Settings.h"
#include "Program/Program.h"
#include "Exceptions/ProgramException.h"
#include "Exceptions/ShaderException.h"
#include "Shaders/Shader.h"

int main() {
    Program::InitializeGLFW();

    try {
        Program::CreateWindowAndAssignContext();
        Program::LoadGladLibrary();
    } catch (const ProgramException& exception) {
        Program::ReportErrorAndTerminate(exception.what());
    }

    Program::SetViewportAndResizerCallback();

    Program::SetDefaultBackgroundToPurple();

    const char* vertexShaderPath = "../src/Shaders/vertexShader.vs";
    const char* fragmentShaderPath = "../src/Shaders/fragmentShader.fs";

    const Shader shaderProgram(vertexShaderPath, fragmentShaderPath);

    try {
        shaderProgram.Load();
    } catch (const ShaderException& exception) {
        Program::ReportErrorAndTerminate(exception.what());
    }

    constexpr float firstTriangle[] = {
        -0.6f,  0.0f, 0.0f,
        0.0f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f,
    };

    constexpr float secondTriangle[] = {
        -0.4f,  0.0f, 0.0f,
        0.2f, -0.8f, 0.0f,
        0.2f, 0.8f, 0.0f,
    };

    // unsigned int indices[] = {
    //     0, 1, 2,
    //     3, 4, 5
    // };

    constexpr int bufferObjectsCount = 2;

    unsigned int VAO[2], VBO[2]; //, EBO[2];
    glGenBuffers(bufferObjectsCount, VBO);
    // glGenBuffers(bufferObjectsCount, EBO);
    glGenVertexArrays(bufferObjectsCount, VAO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(locationIndex, vertexSize, vertexType, normalize, vertexStride, dataPosition);
    glEnableVertexAttribArray(locationIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(locationIndex, vertexSize, vertexType, normalize, vertexStride, dataPosition);
    glEnableVertexAttribArray(locationIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(Program::window))
    {
        Program::ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Program::window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}