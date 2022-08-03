
#type vertex
#version 450 core

layout(location = 0) in vec2 a_Pos;
layout(location = 1) in vec3 a_Colour;

out vec3 v_Colour;

void main()
{
    v_Colour = a_Colour;
    gl_Position = vec4(a_Pos.xy, 0.0, 1.0);
}

#type pixel
#version 450 core

in vec3 v_Colour;

layout(location = 0) out vec4 u_Colour;

void main()
{
    u_Colour = vec4(v_Colour.xyz, 1.0);
}
