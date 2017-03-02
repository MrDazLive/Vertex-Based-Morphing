#version 450

in vec3 o_normal;

out vec4 colour;

void main()
{
    colour = vec4(o_normal / 2 + .5f, 1.0);
}
