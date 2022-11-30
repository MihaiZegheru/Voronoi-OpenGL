#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <window.h>
#include <voronoiseed.h>
#include <mathutility.h>
#include <apptime.h>
#include <renderer.h>
#include <inputmanager.h>
#include <debug.h>


int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;

#define SEEDS_COUNT 3

std::vector <VoronoiSeed*> seeds;


/**
* @brief Window resize callback
*
* @param window
* @param width
* @param height
*
*/
void OnWindowResize(GLFWwindow* window, int width, int height, int deltaWidth, int deltaHeight) {
    for (size_t i = 0; i < seeds.size(); ++i) {
        seeds[i]->SetMovementBounds(glm::vec2(width, height));
        glm::vec2 newPosition = seeds[i]->GetPosition() + glm::vec2(deltaWidth, deltaHeight);
        seeds[i]->SetPosition(newPosition);
    }
}

/**
* @brief Generate random Voronoi Seeds
*
*/
void GenerateSeeds() {
    for (size_t i = 0; i < SEEDS_COUNT; ++i) {
        int windowWidth = Window::GetInstance()->GetWindowWidth();
        int windowHeight = Window::GetInstance()->GetWindowHeight();

        glm::vec2 position;
        position.x = MathUtility::RandomFloat() * windowWidth;
        position.y = MathUtility::RandomFloat() * windowHeight;

        glm::vec4 color;
        color.x = MathUtility::RandomFloat();
        color.y = MathUtility::RandomFloat();
        color.z = MathUtility::RandomFloat();
        color.w = 1.f;

        // TO DO: Add negative velocity
        glm::vec2 velocity;
        velocity.x = MathUtility::Lerp(50, 200, MathUtility::RandomFloat()) * ((MathUtility::RandomFloat() < .5f) ? 1 : -1);
        velocity.y = MathUtility::Lerp(50, 200, MathUtility::RandomFloat()) * ((MathUtility::RandomFloat() < .5f) ? 1 : -1);

        VoronoiSeed* seed = new VoronoiSeed(position, color);
        seed->SetVelocity(velocity);
        seed->SetMovementBounds(glm::vec2(windowWidth, windowHeight));

        seeds.push_back(seed);
    }
}

int main() {
    Window::GetInstance()->Init(WINDOW_WIDTH, WINDOW_HEIGHT, "Voronoi");
    Window::GetInstance()->SetFunctionCallbackOnWindowResize(OnWindowResize);
    int windowWidth = Window::GetInstance()->GetWindowWidth();
    int windowHeight = Window::GetInstance()->GetWindowHeight();

    Time::GetInstance().Init(glfwGetTime());

    InputManager& inputManager = InputManager::GetInstance();

    GLuint shaderProgram = Renderer::Init();

    GLint screenRes = glGetUniformLocation(shaderProgram, "screenRes");
    GLint seedPos = glGetUniformLocation(shaderProgram, "seedPos");
    GLint seedColor = glGetUniformLocation(shaderProgram, "seedColor");
    GLint seedMarkerRadius = glGetUniformLocation(shaderProgram, "seedMarkerRadius");
    GLint seedMarkerColor = glGetUniformLocation(shaderProgram, "seedMarkerColor");
    glUniform2f(screenRes, windowWidth, windowHeight);

    glfwSetInputMode(Window::GetInstance()->GetGlfwInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Generate the Voronoi seeds
    GenerateSeeds();

    bool lastPauseButtonState = false;
    bool isPaused = false;

    while (!glfwWindowShouldClose(Window::GetInstance()->GetGlfwInstance())) {
        
        Time::GetInstance().ComputeDeltaTime(glfwGetTime());
        inputManager.Listen(Window::GetInstance()->GetGlfwInstance());

        if (inputManager.GetKey("pause") && !lastPauseButtonState) {
            isPaused = !isPaused;
        }

        lastPauseButtonState = inputManager.GetKey("pause");

        windowWidth = Window::GetInstance()->GetWindowWidth();
        windowHeight = Window::GetInstance()->GetWindowHeight();

        if (!isPaused) {
            // UPDATE
            Renderer::GenerateDummyVAO();

            // Make a determinstic random sys
            srand(0);

            // Handle Tick()
            for (size_t i = 0; i < seeds.size(); ++i) {
                seeds[i]->Tick(Time::GetInstance().GetDeltaTime());
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Handle Draw
            for (size_t i = 0; i < seeds.size(); ++i) {
                glm::vec2 position = seeds[i]->GetPosition();
                glm::vec4 color = seeds[i]->GetColor();
                float markerRadius = seeds[i]->GetMarkerRadius();
                glm::vec4 markerColor = seeds[i]->GetMarkerColor();

                glUniform2f(screenRes, windowWidth, windowHeight);
                glUniform2f(seedPos, position.x, position.y);
                glUniform4f(seedColor, color.x, color.y, color.z, color.w);
                glUniform1f(seedMarkerRadius, markerRadius);
                glUniform4f(seedMarkerColor, markerColor.x, markerColor.y, markerColor.z, markerColor.w);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }

        glfwSwapBuffers(Window::GetInstance()->GetGlfwInstance());
        glfwPollEvents();
    }

    Renderer::Destroy();

    glfwDestroyWindow(Window::GetInstance()->GetGlfwInstance());
    glfwTerminate();

    return 0;
}