#include "Log.h"

#include <iostream>
#include <GL/glew.h>

void GLClearError()
{
    while(GLenum error = glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Logger(const char* mess, const char* file, int line) {
    std::cout << "[3DsMIN INFO] (" << mess << "): " << file << ":" << line << std::endl;
}