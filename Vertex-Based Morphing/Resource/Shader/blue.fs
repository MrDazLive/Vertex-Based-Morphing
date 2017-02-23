#version 450

in vec2 o_uv;

out vec4 colour;

void main()
{
    colour = vec4(o_uv, 0.0, 1.0);
}
