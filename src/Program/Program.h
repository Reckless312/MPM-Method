#ifndef MPM_METHOD_PROGRAM_H
#define MPM_METHOD_PROGRAM_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Program {
public:
    static GLFWwindow* window;

    static void InitializeGLFW();
    static void CreateWindowAndAssignContext();
    static void LoadGladLibrary();
    static void SetViewportAndResizerCallback();
    static void ResizeWindow(GLFWwindow* createdWindow, int width, int height);
    static void SetDefaultBackgroundToPurple();
    static void ProcessInput();

    static int ReportErrorAndTerminate(const char* errorMessage);
private:
    static constexpr int majorVersion = 3;
    static constexpr int minorVersion = 3;

    static constexpr int profile = GLFW_OPENGL_CORE_PROFILE;

    static constexpr GLsizei windowWidth = 800;
    static constexpr GLsizei windowHeight = 600;

    inline static const char* windowTitle = "MPM Snow Simulation";

    inline static GLFWmonitor* fullscreenMonitor = nullptr;
    inline static GLFWwindow* windowToShareResources = nullptr;

    static constexpr int failureCode = 1;

    static constexpr GLint viewportBottomLeftX = 0;
    static constexpr GLint viewportBottomLeftY = 0;
};


#endif