#pragma once

const char sk_vshader[] =
        "#version 330\n"
        "layout (location = 0) in vec3 vPosition;\n"
        "layout (location = 1) in vec4 vColor;\n"
        "layout (location = 2) in vec2 vIndex;\n"
        "layout (location = 3) in vec2 vWeight;\n"
        "out vec4 col;\n"
        "uniform mat4 MVmat;\n"
        "uniform mat4 ProjMat;\n"
        "uniform mat4 Bone[10];\n"  // Array of bones that you compute (animate) on the CPU and you upload to the shader
        "void main()\n"
        "{\n"
        "vec4 newVertex;\n"
        "vec4 newNormal;\n"
        "int index;\n"
        "// --------------------\n"
        "index=int(Index.x);\n"  // Cast to int
        "newVertex = (Bone[index] * vec4(vPosition, 1.0)) * Weight.x;\n"
        "index=int(Index.y);\n"  //Cast to int
        "newVertex = (Bone[index] * vec4(vPosition, 1.0)) * Weight.y + newVertex;\n"
        "gl_Position = ProjMat * MVmat * newVertex;\n"
        "col = vColor;\n"
        "}\n";


const char sk_fshader[] =
        "#version 330\n"
        "in vec4 col;\n"
        "out vec4 fragColor;\n"
        "uniform vec4 color;\n"
                "uniform vec4 additive;\n"
                "void main()\n"
                "{\n"
                "fragColor = col;\n"
                "fragColor *= color;\n"
                "fragColor += additive;\n"
                "}\n";



// Vertex Shader
