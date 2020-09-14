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
				"uniform mat3 nMat;\n"			// the normal matrix
                "out vec2 tex;\n"
                "out vec3 Normal;\n"
				"out vec4 eye;\n"
                "out mat4 mv;\n"
                "void main()\n"
                "{\n"
                "tex = vTexture;\n"
				"Normal = normalize(nMat * vNormal);\n"
	            "eye = - (MVmat * vec4(vPosition, 1.0));\n"
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 1.0);\n"
				//"FragPos = vec3(modelMat * vec4(vPosition, 1.0));"
                "}\n";

const char fs_tex_light[] =
        "#version 330\n"
                "\n"
                "in vec2 tex;\n"
                "in vec3 Normal;\n"
				"in vec4 eye;\n"
                //"in mat4 mv;\n"
                "uniform sampler2D Tex1;\n"
                "uniform vec3 lightDir;\n"
                "uniform vec4 diffuse;\n"
                "uniform vec4 ambient;\n"
                "out vec4 fragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "vec3 n = normalize(Normal);\n"
				"vec3 e = normalize(vec3(eye));\n"
                //"norm = Normal;\n"
                "vec4 texColor = texture (Tex1, tex);\n"
                "//if (texColor.a < 0.5)\n"
                "//discard;\n"
				"float intensity = max (dot(n, -lightDir), 0.0);\n"
                "vec4 d = (intensity * diffuse + ambient) * texColor;\n"
                //"texColor *= vec4(diffuse, 1.0);\n"
                "fragColor = d;//max(intensity * texColor * diffuse, ambient);\n"
                "}\n";