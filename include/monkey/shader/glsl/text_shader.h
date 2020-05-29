#pragma once

const char text_vshader[] =
        "#version 330\n"
                "\n"
                "layout (location = 0) in vec2 vPosition;\n"
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
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 0.0, 1.0);\n"
                "}\n"
;

const char text_fshader[] =
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
                "texColor = texColor.rrrr * col;\n"
                "if (texColor.a < 0.5)\n"
                "discard;\n"
                "texColor *= color;\n"
                "texColor += additive;\n"
                "fragColor = texColor;\n"
                "}\n"
;

