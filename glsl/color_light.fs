#version 330 core

in vec4 col;
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
    float intensity = max (dot(n, -lightDir), 0.0);
    //intensity *= smoothstep(1.0, 0.2, gl_FragDepth);
    vec4 d = (intensity * diffuse + ambient) * col;
    fragColor = d;
}