#include "Program.h"
#include "../Exceptions/ProgramException.h"

#include <iostream>
#include <ostream>

GLFWwindow* Program::window = nullptr;

void Program::InitializeGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Program::majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Program::minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, Program::profile);
}

void Program::CreateWindowAndAssignContext() {
    Program::window = glfwCreateWindow(Program::windowWidth, Program::windowHeight, Program::windowTitle, Program::fullscreenMonitor, Program::windowToShareResources);

    if (Program::window == nullptr)
    {
        throw ProgramException("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(Program::window);
}

void Program::LoadGladLibrary() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw ProgramException("Failed to initialize GLAD.");
    }
}

void Program::SetViewportAndResizerCallback() {
    glViewport(Program::viewportBottomLeftX, Program::viewportBottomLeftY, Program::windowWidth, Program::windowHeight);

    glfwSetFramebufferSizeCallback(Program::window, Program::ResizeWindow);
}

void Program::ResizeWindow(GLFWwindow *createdWindow, const int width, const int height) {
    glViewport(Program::viewportBottomLeftX, Program::viewportBottomLeftY, width, height);
}

void Program::SetDefaultBackgroundToPurple() {
    constexpr float red = 0.239f, green = 0.122f, blue = 0.361f, alpha = 1.0f;

    glClearColor(red, green, blue, alpha);
}

void Program::ProcessInput() {
    if (glfwGetKey(Program::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Program::window, true);
    }
}

int Program::ReportErrorAndTerminate(const char *errorMessage) {
    std::cout << errorMessage << std::endl;
    glfwTerminate();
    return Program::failureCode;
}