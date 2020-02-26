#pragma once

const char basic_vshader_light[] =
        "#version 330 core\n"
                "layout (location = 0) in vec3 position;\n"
                "layout (location = 1) in vec3 normal;\n"
                "layout (location = 2) in vec4 color;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
                "out vec4 col;\n"
                "out vec3 Normal;\n"
                "void main()\n"
                "{\n"
                "col = color;\n"
                "gl_Position = ProjMat * MVmat * vec4(position, 1.0);\n"
                "Normal = normal;\n"
                "}\n"
;
const char basic_fshader_light[] =
        "#version 330 core\n"
                "in vec4 col;\n"
                "out vec4 fragColor;\n"
                "uniform vec3 lightColor;\n"
                "void main()\n"
                "{\n"
                "fragColor = vec4(1.0); // * vec4(lightColor, 1.0);\n"
                "}\n"
;
