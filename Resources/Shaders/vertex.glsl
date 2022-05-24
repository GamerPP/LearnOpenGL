#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texPos;

out vec3 oColor;
out vec2 oTexPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    oColor = aColor;
    oTexPos = vec2(texPos.x, 1.0f-texPos.y);
}