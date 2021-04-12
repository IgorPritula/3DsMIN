#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;
in float TexID;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture1;
uniform float opacity;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
    //        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    // ambient
    float ambientStrength = 0.5;
    vec4 lightColor4 = vec4(lightColor, 1.0);
    vec4 ambient = ambientStrength * lightColor4;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.01);
    vec4 diffuse = diff * lightColor4;
    if (int(TexID) < 0) {
        FragColor = (ambient + diffuse) * Color;
    }
    else {
        FragColor = (ambient + diffuse) * Color * texture(texture1, TexCoord);
    }
    
    
}
