#version 130

in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 color;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    color = vertexColor;
}