#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;
        
uniform mat4 modelview;
uniform mat4 projection;
			
uniform mat3 normal;

out vec2 tex;
out vec3 Normal;
out vec4 eye;
out mat4 mv;
                
void main()
{
    tex = vTexture;
    Normal = normalize(normal * vNormal);
    eye = -(modelview * vec4(vPosition, 1.0));
    gl_Position = projection * modelview * vec4(vPosition, 1.0);
}
