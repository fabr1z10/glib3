#version 330 core

in vec2 pass_texCoord;

out vec4 fragColor;

uniform sampler2D texture_diffuse1;
uniform vec4 color;
uniform vec4 additive;

void main()
{
    vec4 diffuseColor = texture(texture_diffuse1, pass_texCoord);
	//diffuseColor *= color;
	//diffuseColor += additive;\n"
    fragColor = diffuseColor;
}
        