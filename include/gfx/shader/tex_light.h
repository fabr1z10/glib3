#pragma once

// the basic (unlit) textured shader
const char vs_tex_light[] =
        "#version 330\n"
                "\n"
                "layout (location = 0) in vec3 vPosition;\n"
                "layout (location = 1) in vec2 vTexture;\n"
                "layout (location = 2) in vec3 vNormal;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
                "out vec2 tex;\n"
                "out vec3 Normal;\n"
                "void main()\n"
                "{\n"
                "tex = vTexture;\n"
                "Normal = vNormal;\n"
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 1.0);\n"
                "}\n";

const char fs_tex_light[] =
        "#version 330\n"
                "\n"
                "in vec2 tex;\n"
                "in vec3 Normal;\n"
                "uniform sampler2D Tex1;\n"
                "uniform vec3 lightDir;\n"
                "uniform vec3 lightColor;\n"
                "uniform vec3 ambient;\n"
                "out vec4 fragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "vec3 norm = normalize(Normal);\n"
                "norm = Normal;\n"
                "vec4 texColor = texture (Tex1, tex);\n"
                "if (texColor.a < 0.5)\n"
                "discard;\n"
                "float diff = max(dot(norm, lightDir), 0.0);\n"
                "vec3 diffuse = diff * lightColor + ambient;\n"
                "texColor *= vec4(diffuse, 1.0);\n"
                "fragColor = texColor;\n"
                "}\n";
