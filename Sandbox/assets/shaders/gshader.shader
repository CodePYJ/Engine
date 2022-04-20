#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aColor;
layout(location = 4) in float aSpecilar;

layout(std140, binding = 0) uniform Camera
{
    mat4 projection;
    mat4 view;
};

uniform mat4 u_transform;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out vec3 Color;
out float Specilar;

void main()
{
    vec4 world_pos = u_transform * vec4(aPos, 1.0);
    FragPos = world_pos.xyz;
    gl_Position = projection * view * u_transform * vec4(aPos, 1.0);
    TexCoords = aTexCoord;
    mat3 normalMat3 = transpose(inverse(mat3(u_transform)));        // ???
    Normal = normalMat3 * aNormal;
    Color = aColor;
    Specilar = aSpecilar;
}


#shader fragment
#version 450 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in float Specilar;

void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gAlbedoSpec.rgb = Color;
    gAlbedoSpec.a = Specilar;
}