#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform int highlight; // 0 for no highlight, 1 for highlight

void main() {
    vec4 texColor = texture(texture1, TexCoord);

    if (highlight == 1) {
        texColor.rgb = texColor.rgb * vec3(1.0, 0.5, 0.5); // Example: red tint for highlighting
    }

    FragColor = texColor;
}
