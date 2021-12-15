#version 330 core

in vec2 tex;
in vec3 Normal;
in vec4 eye;

uniform sampler2D texture_diffuse1;
uniform vec3 lightDir;
uniform vec4 diffuse;
uniform vec4 ambient;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(Normal);
    vec3 e = normalize(vec3(eye));
    vec4 texColor = texture (texture_diffuse1, tex);
    float intensity = max (dot(n, -lightDir), 0.0);
    vec4 d = (intensity * diffuse + ambient) * texColor;
    fragColor = d;
}