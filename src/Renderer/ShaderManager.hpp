#ifndef shadermanager_hpp
#define shadermanager_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderManager {
private:
    // the program ID
    unsigned int m_ID;
    std::string vertexCode;
    std::string fragmentCode;
public:
    
    // constructor reads and builds the shader
    ShaderManager(const GLchar*, const GLchar*);
    ~ShaderManager();
    
    void loadShader(const GLchar*, const GLchar*);
    
    // use/activate the shader
    void use();
    
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const;
    void setMatrix4fv(const std::string &name, glm::mat4 trans);
    void setMatrix3fv(const std::string &name, glm::mat3 trans);
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
};

#endif /* shadermanager_hpp */
