#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
//layout(location = 4) in int aEntityID;

//out vec3 color;
//out flat int entity;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
    //color = aColor;
    //entity = aEntityID;
    Normal = aNormal;
    FragPos = aPos;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
//layout(location = 1) out int color1;

//in vec3 color;
//in flat int entity;

in vec3 Normal;
in vec3 FragPos;


void main()
{
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec3 lightPos = vec3(2.0, 2.0, -2.0);

    float ambientStrength = 0.4;
    vec4 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec4 result = (diffuse + ambient) * vec4(0.5, 0.5, 0.5, 1.0);

    color0 = result;
    //color1 = entity;
}
