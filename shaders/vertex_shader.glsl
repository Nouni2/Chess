#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projection; // Projection matrix
uniform vec3 offset;
uniform mat4 rotation;   // Rotation matrix

void main() {
    vec4 transformedPos = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z + offset.z, 1.0);
    transformedPos = rotation * transformedPos;  // Apply rotation
    gl_Position = projection * transformedPos;   // Apply projection
    TexCoord = aTexCoord;
}
