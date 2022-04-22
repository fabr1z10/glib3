#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec4 vColor;

uniform mat4 modelview;
uniform mat4 projection;
uniform mat3 normal;

out vec4 col;
out vec3 Normal;
out vec4 eye;
                
void main()
{
    Normal = normalize(normal * vNormal);
    eye = -(modelview * vec4(vPosition, 1.0));
    col = vColor;
    gl_Position = projection * modelview * vec4(vPosition, 1.0);
}