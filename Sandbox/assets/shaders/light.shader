#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

layout(std140, binding = 0) uniform Camera
{
    mat4 projection;
    mat4 view;
};

uniform mat4 u_transform;

void main()
{
    gl_Position = projection * view * u_transform * vec4(aPos, 1.0);
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

layout(std140, binding = 1) uniform Light
{
    mat4 light_property;
};

uniform vec3 u_color;
uniform int u_entity;

void main()
{
    color0 = vec4(u_color, 1.0f);
    color1 = u_entity;
}