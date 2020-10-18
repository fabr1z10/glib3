#pragma once

// this is the shader used for drawing shapes.
// It just draws a colored outline of the shapes
const char vs_race[] =
        "#version 330 core\n"
        "layout (location = 0) in vec3 vPosition;\n"
        "layout (location = 1) in vec4 vColor;\n"
        "uniform mat4 MVmat;\n"
        "uniform mat4 ProjMat;\n"
        "out vec4 col;\n"
        "void main()\n"
        "{\n"
        "col = vColor;\n"
        "gl_Position = ProjMat * MVmat *  vec4(vPosition, 1.0);\n"
        "}\n";

const char fs_race[] =
        "#version 330\n"
        "\n"
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
