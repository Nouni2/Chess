#include "shaders.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "log.h" // Include the logger

extern Logger logger;  // Use the global logger

unsigned int loadShaders(const std::string& vertexPath, const std::string& fragmentPath) {
    logger.log(LogLevel::INFO, "Loading shaders.");
    logger.log(LogLevel::DEBUG, "Vertex shader path: " + vertexPath);
    logger.log(LogLevel::DEBUG, "Fragment shader path: " + fragmentPath);

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        logger.log(LogLevel::ERROR, "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        logger.log(LogLevel::ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
    } else {
        logger.log(LogLevel::INFO, "Vertex shader compiled successfully.");
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        logger.log(LogLevel::ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog));
    } else {
        logger.log(LogLevel::INFO, "Fragment shader compiled successfully.");
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        logger.log(LogLevel::ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
    } else {
        logger.log(LogLevel::INFO, "Shader program linked successfully.");
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    logger.log(LogLevel::DEBUG, "Shader objects deleted after linking.");

    return shaderProgram;
}
