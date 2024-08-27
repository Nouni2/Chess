#version 330 core

out vec4 color;

uniform vec3 squareColor;

void main() {
    color = vec4(squareColor, 1.0);
}
