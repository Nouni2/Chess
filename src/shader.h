#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

std::string loadShaderSource(const std::string& filepath);
GLuint compileShader(GLenum type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

#endif // SHADER_H
