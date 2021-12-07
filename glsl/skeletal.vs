#version 330 core
    
const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;
        
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in ivec3 vIndex;
layout (location = 3) in vec3 vWeight;

out vec2 pass_texCoord;
        
uniform mat4 modelview;
uniform mat4 projection;
uniform mat4 Bone[MAX_JOINTS];  // Array of bones that you compute (animate) on the CPU and you upload to the shader

void main()
{
    vec4 totalLocalPos = vec4(0.0);
    vec4 localPosition0 = Bone[vIndex[0]] * vec4(vPosition, 1.0);
    vec4 localPosition1 = Bone[vIndex[1]] * vec4(vPosition, 1.0);
    vec4 localPosition2 = Bone[vIndex[2]] * vec4(vPosition, 1.0);
    totalLocalPos += localPosition0 * vWeight[0] + localPosition1 * vWeight[1] + localPosition2 * vWeight[2];
    pass_texCoord= vTexture;
    totalLocalPos = vec4(vPosition, 1.0);
    gl_Position = projection * modelview * totalLocalPos;
}