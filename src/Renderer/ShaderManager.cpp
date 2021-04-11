#include <iostream>
#include "ShaderManager.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include "Log.h"

ShaderManager::ShaderManager(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    loadShader(vertexPath, fragmentPath);
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
    GLCall(glCompileShader(vertex));
    // print compile errors if any
    GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCall(glCompileShader(fragment));
    // print compile errors if any
    GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // shader Program
    m_ID = glCreateProgram();
    GLCall(glAttachShader(m_ID, vertex));
    GLCall(glAttachShader(m_ID, fragment));
    GLCall(glLinkProgram(m_ID));
    // print linking errors if any
    GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
    if(!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessery
    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));
}

void ShaderManager::loadShader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void ShaderManager::use()
{
    GLCall(glUseProgram(m_ID));
}

void ShaderManager::setInt(const std::string &name, int value) const
{
    GLCall(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value));
}

// ------------------------------------------------------------------------
void ShaderManager::setFloat(const std::string &name, float value) const
{
    GLCall(glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value));
}

void ShaderManager::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const
{
    
}

void ShaderManager::setMatrix4fv(const std::string &name, glm::mat4 trans) {
    GLCall(glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans)));
}

void ShaderManager::setMatrix3fv(const std::string &name, glm::mat3 trans) {
    GLCall(glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans)));
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) const
{
    GLCall(glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]));
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) const
{
    GLCall(glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]));
}

ShaderManager::~ShaderManager() {
    GLCall(glDeleteProgram(m_ID));
}

