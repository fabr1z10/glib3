#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 col;

uniform mat4 modelview;
uniform mat4 projection;

void main()
{
	col = vColor;
	gl_Position = projection * modelview * vec4(vPosition, 1.0);
}
