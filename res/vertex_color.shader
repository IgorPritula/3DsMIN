#version 330 core
layout (location = 0) in vec3 aPos;  // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in float aTexID;

out vec4 Color;
out vec2 TexCoord;
out float TexID;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 uPerspective;
uniform mat4 uTransform;
uniform mat3 uNormalTrans;
uniform vec3 uColor;

// output a color to the fragment shader
void main()
{
    gl_Position = uPerspective * uTransform * vec4(aPos, 1.0f);
    FragPos = vec3(uTransform * vec4(aPos, 1.0));
    if(uColor.x > 0) {
        Color = vec4(uColor, 1.0);
    }
    else {
        Color = vec4(aColor, 1.0);
    }
    TexCoord = aTexCoord;
    TexID = aTexID;
    Normal = uNormalTrans * aNormal;
}
