#version 330 core
out vec4 FragColor;

in vec3 oColor;
in vec2 oTexPos;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
    FragColor = mix(texture(uTexture1, oTexPos), texture(uTexture2, oTexPos), 0.5);
}