#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 tile_transform;

void main() {
    gl_Position = tile_transform * vec4(position, 0.5, 1.0);
}