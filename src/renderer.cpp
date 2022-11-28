#include <renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>



const int MAX_LIGHTS_COUNT = 100;

GLuint PointLightBuffer;
void* mappedLightBuffer;



GLuint CreateDefaultShaderProgram(std::vector<char> fragmentShaderBuffer, std::vector<char> vertexShaderBuffer)
{
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSourceString = std::string(vertexShaderBuffer.begin(), vertexShaderBuffer.end());
    const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int successStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successStatus);
    char infoLog[512];
    if (!successStatus)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSourceString = std::string(fragmentShaderBuffer.begin(), fragmentShaderBuffer.end());
    const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successStatus);
    if (!successStatus)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successStatus);
    if (!successStatus)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << infoLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::vector<char> ReadShader(std::string path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    size_t fileLen = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileLen, 0);
    file.seekg(0);
    file.read(buffer.data(), fileLen);
    file.close();

    return buffer;
}

void InitShaders()
{
    std::vector<char> fragmentShaderBuffer = ReadShader("../src/shaders/defaultfragmentshader.glsl");
    std::vector<char> vertexShaderBuffer = ReadShader("../src/shaders/defaultvertexshader.glsl");
    GLuint shaderProgram = CreateDefaultShaderProgram(fragmentShaderBuffer, vertexShaderBuffer);
    glUseProgram(shaderProgram);
}

void InitGL()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Init()
{
    InitShaders();
    InitGL();
}

void Renderer::Destroy()
{
    // unload all
}

