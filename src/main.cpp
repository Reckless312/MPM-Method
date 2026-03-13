#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL/Scene/Camera.h"
#include "OpenGL/Program.h"
#include "Exceptions/MPMException.h"
#include "OpenGL/Model/Model.h"
#include "OpenGL/Shaders/Shader.h"
#include "OpenGL/Shaders/TextureLoader.h"

int main()
{
    Program program;

    try
    {
        Program::InitializeGLFW();
        program.CreateWindowAndAssignContext();

        Program::LoadGladLibrary();
        program.LockCursor();
    }
    catch (const MPMException& exception)
    {
        return Program::ReportErrorAndTerminate(exception);
    }

    program.SetViewportAndResizeCallback();

    Camera camera(program.window, Program::windowWidth, Program::windowHeight);
    camera.AssignUserPointerAndSetCallbacks();

    Model snowTerrain("/home/cora/GitHub/MPM-Method/src/Assets/snow_mountain.obj");

    try
    {
        snowTerrain.loadModel();
    }
    catch (const MPMException& exception)
    {
        return Program::ReportErrorAndTerminate(exception);
    }

    Shader sceneShader("vertexShader.vs", "fragmentShader.fs");

    try
    {
        sceneShader.Load();
    }
    catch (const MPMException& exception)
    {
        return Program::ReportErrorAndTerminate(exception);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -35.0f, 0.0f));
    model = glm::scale(model, glm::vec3(500.0f));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(program.window))
    {
        program.UpdateDeltaTime();
        camera.UpdateSpeed(program.deltaTime);

        program.ProcessInput();
        camera.ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneShader.Use();

        sceneShader.SetMat4("model", model);
        sceneShader.SetMat4("view", camera.viewMatrix);
        sceneShader.SetMat4("projection", camera.projectionMatrix);
        sceneShader.SetMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

        sceneShader.SetVec3("viewPosition", camera.position);
        sceneShader.SetFloat("material.shininess", 32.0f);

        sceneShader.SetVec3("directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        sceneShader.SetVec3("directionalLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
        sceneShader.SetVec3("directionalLight.diffuse", glm::vec3(0.7f, 0.7f, 0.7f));
        sceneShader.SetVec3("directionalLight.specular", glm::vec3(0.8f, 0.8f, 0.8f));

        snowTerrain.Draw(sceneShader);

        glfwSwapBuffers(program.window);
        glfwPollEvents();
    }

    return 0;
}