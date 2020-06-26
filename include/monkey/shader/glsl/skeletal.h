#pragma once

const char sk_vshader[] =
        "#version 330\n"
        "const int MAX_JOINTS = 50;\n"
        "const int MAX_WEIGHTS = 3;\n"
        "layout (location = 0) in vec3 vPosition;\n"
        "layout (location = 1) in vec2 vTexture;\n"
        "layout (location = 2) in ivec3 vIndex;\n"
        "layout (location = 3) in vec3 vWeight;\n"
        "out vec2 pass_texCoord;\n"
        "uniform mat4 MVmat;\n"
        "uniform mat4 ProjMat;\n"
        "uniform mat4 Bone[MAX_JOINTS];\n"  // Array of bones that you compute (animate) on the CPU and you upload to the shader
        "void main()\n"
        "{\n"
        "vec4 totalLocalPos = vec4(0.0);\n"
        "for (int i = 0; i <MAX_WEIGHTS; i++) {\n"
        "    vec4 localPosition = Bone[vIndex[i]] * vec4(vPosition, 1.0);\n"
        "    totalLocalPos += localPosition * vWeight[i];\n"
        "}\n"
        "gl_Position = ProjMat * MVmat * totalLocalPos;\n"
        "pass_texCoord= vTexture;\n"
        "}\n";


const char sk_fshader[] =
        "#version 330\n"
        "in vec2 pass_texCoord;\n"
        "out vec4 fragColor;\n"
        "uniform sampler2D tex1;\n"
        "uniform vec4 color;\n"
        "uniform vec4 additive;\n"
        "void main()\n"
        "{\n"
        "    vec4 diffuseColor = texture(tex1, pass_texCoord);\n"
        "    fragColor = diffuseColor;\n"
        //        "fragColor *= color;\n"
        //        "fragColor += additive;\n"
        "}\n";



// Vertex Shader
