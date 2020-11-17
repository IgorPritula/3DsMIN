#version 330 core
layout (location = 0) in vec3 aPos;  // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in float aTexID;

out vec4 Color;
out vec2 TexCoord;
out float TexID;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 perspective;
uniform mat4 transform;

// output a color to the fragment shader
void main()
{
    gl_Position = perspective * transform * vec4(aPos, 1.0f);
    FragPos = vec3(transform * vec4(aPos, 1.0));
    Color = aColor; // set ourColor to the input color we got from the vertex data
    TexCoord = aTexCoord;
    TexID = aTexID;
    Normal = aNormal;
}
