#version 330 core

out vec4 fragColor;

in vec2 tex;
in vec4 col;

uniform sampler2D Tex1;
uniform vec4 add_color;
uniform vec4 mult_color;

void main()
{
	vec4 texColor = texture(Tex1, tex)
	if (texColor.a < 0.5) {
		discard;
	}
	texColor *= col;
	texColor *= mult_color;
	texColor += add_color;
	fragColor = texColor;
}



