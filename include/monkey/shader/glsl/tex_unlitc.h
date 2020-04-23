#pragma once

// the basic (unlit) textured shader
const char vs_tex_unlitc[] =
        "#version 330\n"
                "\n"
                "layout (location = 0) in vec3 vPosition;\n"
                "layout (location = 1) in vec2 vTexture;\n"
                "layout (location = 2) in vec4 vColor;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
                "out vec2 tex;\n"
                "out vec4 col;\n"
                "void main()\n"
                "{\n"
                "tex = vTexture;\n"
                "col = vColor;\n"
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 1.0);\n"
                "}\n";

const char fs_tex_unlitc[] =
        "#version 330\n"
                "\n"
                "in vec2 tex;\n"
                "in vec4 col;\n"
                "uniform sampler2D Tex1;\n"
                "uniform vec4 color;\n"
                "uniform vec4 additive;\n"
                "out vec4 fragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "vec4 texColor = texture (Tex1, tex);\n"
                "if (texColor.a < 0.5)\n"
                "discard;\n"
                "texColor *= color;\n"
                "texColor *= col;\n"
                "texColor += additive;\n"
                "fragColor = texColor;\n"
                "}\n";
