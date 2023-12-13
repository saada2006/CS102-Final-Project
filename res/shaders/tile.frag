#version 330 core

uniform vec3 tile_color;

out vec4 color;

void main() {
    color = vec4(tile_color, 1.0);
}