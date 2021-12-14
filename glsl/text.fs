#version 330 core

out vec4 fragColor;

in vec2 tex;
in vec4 col;
                
uniform sampler2D texture_diffuse1;

uniform vec4 mult_color;
//uniform vec4 additive;
        

void main()
{
    vec4 texColor = texture(texture_diffuse1, tex);
    texColor = texColor.rrrr * col;
    //if (texColor.a < 0.5)
    //    discard;
    texColor *= mult_color;
    fragColor = texColor;                
}