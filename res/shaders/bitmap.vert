#version 330 core

layout(location = 0) in vec4 position;

out vec2 tex_coords;

uniform mat4 tile_transform;

void main() {
    gl_Position = tile_transform * vec4(position.xy, 0.5, 1.0);

    tex_coords = position.zw;
}