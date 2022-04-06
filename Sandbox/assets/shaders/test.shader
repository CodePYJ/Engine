#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

out vec3 color;

uniform mat4 transform;
uniform mat4 u_ViewProjection;
uniform vec3 u_color;

void main()
{
    gl_Position = u_ViewProjection * transform * vec4(aPos, 1.0);
    color = u_color;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

uniform int entity;

in vec3 color;

void main()
{
    color0 = vec4(color,1.0);
    color1 = entity;
}
