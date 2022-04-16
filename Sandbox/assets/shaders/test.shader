#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
layout(location = 4) in int aTexIndex;
layout(location = 5) in int aEntityID;

out vec3 color;
out vec2 texCoord;
out flat int texIndex;
out flat int entity;

layout(std140, binding=0) uniform Camera
{
    mat4 projection;
    mat4 view;
};

//uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    color = aColor;
    entity = aEntityID;
    texCoord = aTexCoord;
    texIndex = aTexIndex;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

in vec3 color;
in vec2 texCoord;
in flat int texIndex;
in flat int entity;

layout(binding = 0) uniform sampler2D u_textures[4];

void main()
{
    vec4 texColor = vec4(color, 1.0);

    switch (texIndex)
    {
        case 0:texColor *= texture(u_textures[0], texCoord); break;
        case 1:texColor *= texture(u_textures[1], texCoord); break;
        case 2:texColor *= texture(u_textures[2], texCoord); break;
        case 3:texColor *= texture(u_textures[3], texCoord); break;
    }

    color0 = texColor;
    color1 = entity;
}
