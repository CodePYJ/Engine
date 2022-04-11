#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
layout(location = 4) in int aEntityID;

out vec3 color;
out flat int entity;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
    color = aColor;
    entity = aEntityID;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

in vec3 color;
in flat int entity;

void main()
{
    color0 = vec4(color, 1.0);
    color1 = entity;
}
