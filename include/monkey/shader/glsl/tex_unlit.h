#pragma once

// the basic (unlit) textured shader
const char vs_tex_unlit[] =
        "#version 330\n"
                "\n"
                "layout (location = 0) in vec3 vPosition;\n"
                "layout (location = 1) in vec2 vTexture;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
		        "uniform int forceZ;"
		        "uniform float forcedZ;"
                "out vec2 tex;\n"
                "void main()\n"
                "{\n"
                "tex = vTexture;\n"
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 1.0);\n"
		        "if (forceZ == 1) { gl_Position.z = forcedZ * gl_Position.w; }\n"

                "}\n";

const char fs_tex_unlit[] =
        "#version 330\n"
                "\n"
                "in vec2 tex;\n"
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
                "texColor += additive;\n"
                "fragColor = texColor;\n"
                "}\n";
