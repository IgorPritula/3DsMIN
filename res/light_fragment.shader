#version 330 core
out vec4 FragColor;

in vec4 Color;

void main()
{
    FragColor = Color; // set alle 4 vector values to 1.0
}
