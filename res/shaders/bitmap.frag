#version 330 core

uniform sampler2D bitmap;

in vec2 tex_coords;

out vec4 color;

void main() {
    color = texture(bitmap, tex_coords);
}