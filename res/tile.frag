#version 330 core

uniform vec3 tile_color;

out vec3 color;

void main() {
    color = tile_color;
}