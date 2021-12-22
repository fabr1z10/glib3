#version 330 core
    
const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;
        
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
//layout (location = 2) in ivec3 vIndex;
layout (location = 2) in vec3 vWeight;

out vec3 pass_color;
        
uniform mat4 modelview;
uniform mat4 projection;
uniform mat4 local_to_model;
uniform ivec3 weightIndex;
uniform mat4 Bone[MAX_JOINTS];  // Array of bones that you compute (animate) on the CPU and you upload to the shader

void main()
{
    // convert local to model
    vec4 modelpos = local_to_model * vec4(vPosition, 1.0);
    vec4 totalLocalPos = vec4(0.0);
    vec4 localPosition0 = Bone[weightIndex[0]] * modelpos;
    vec4 localPosition1 = Bone[weightIndex[1]] * modelpos;
    vec4 localPosition2 = Bone[weightIndex[2]] * modelpos;
    totalLocalPos += localPosition0 * vWeight[0] + localPosition1 * vWeight[1] + localPosition2 * vWeight[2];
    totalLocalPos.z = modelpos.z;
    pass_color= vColor;
    //totalLocalPos = vec4(vPosition, 1.0);
    gl_Position = projection * modelview * totalLocalPos;
}