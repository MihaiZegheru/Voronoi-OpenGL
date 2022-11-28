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
#include <apptime.h>
#include <renderer.h>
#include <debug.h>


int WINDOW_WIDTH = 2000;
int WINDOW_HEIGHT = 900;

#define SEEDS_COUNT 20 

std::vector <VoronoiSeed*> seeds;


void OnWindowResize(GLFWwindow* window, int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (size_t i = 0; i < seeds.size(); ++i) {
        seeds[i]->SetMovementBounds(glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    }
    // TO DO: Update positions
}

float RandomFloat() {
    return (float)rand() / RAND_MAX;
}

float Lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}

void GenerateDummyVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void GenerateSeeds() {
    for (size_t i = 0; i < SEEDS_COUNT; ++i) {
        glm::vec2 position;
        position.x = RandomFloat() * WINDOW_WIDTH;
        position.y = RandomFloat() * WINDOW_HEIGHT;

        glm::vec4 color;
        color.x = RandomFloat();
        color.y = RandomFloat();
        color.z = RandomFloat();
        color.w = 1.f;

        glm::vec2 velocity;
        velocity.x = Lerp(100, 300, RandomFloat()) * ((RandomFloat() < .5f) ? 1 : -1);
        velocity.y = Lerp(100, 300, RandomFloat()) * ((RandomFloat() < .5f) ? 1 : -1);

        VoronoiSeed* seed = new VoronoiSeed(position, color);
        seed->SetVelocity(velocity);
        seed->SetMovementBounds(glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

        seeds.push_back(seed);
    }
}

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Voronoi");

    Time::GetInstance().Init(glfwGetTime());

    GLuint shaderProgram = Renderer::Init();

    glfwSetFramebufferSizeCallback(window.GetInstance(), OnWindowResize);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2, 0.2, 0.2, 1);

    GLint screenRes = glGetUniformLocation(shaderProgram, "screenRes");
    GLint seedPos = glGetUniformLocation(shaderProgram, "seedPos");
    GLint seedColor = glGetUniformLocation(shaderProgram, "seedColor");
    GLint seedMarkerRadius = glGetUniformLocation(shaderProgram, "seedMarkerRadius");
    GLint seedMarkerColor = glGetUniformLocation(shaderProgram, "seedMarkerColor");
    glUniform2f(screenRes, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetInputMode(window.GetInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Generate the Voronoi seeds
    GenerateSeeds();

    while (!glfwWindowShouldClose(window.GetInstance())) {
        Time::GetInstance().ComputeDeltaTime(glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GenerateDummyVAO();
        
        // Make a determinstic random sys
        srand(0);

        // Handle Tick()
        for (size_t i = 0; i < seeds.size(); ++i) {
            seeds[i]->Tick(Time::GetInstance().GetDeltaTime());
        }

        // Handle Draw
        for (size_t i = 0; i < seeds.size(); ++i) {
            glm::vec2 position = seeds[i]->GetPosition();
            glm::vec4 color = seeds[i]->GetColor();
            float markerRadius = seeds[i]->GetMarkerRadius();
            glm::vec4 markerColor = seeds[i]->GetMarkerColor();

            glUniform2f(seedPos, position.x, position.y);
            glUniform4f(seedColor, color.x, color.y, color.z, color.w);
            glUniform1f(seedMarkerRadius, markerRadius);
            glUniform4f(seedMarkerColor, markerColor.x, markerColor.y, markerColor.z, markerColor.w);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        glfwSwapBuffers(window.GetInstance());
        glfwPollEvents();
    }

    Renderer::Destroy();

    glfwDestroyWindow(window.GetInstance());
    glfwTerminate();

    return 0;
}