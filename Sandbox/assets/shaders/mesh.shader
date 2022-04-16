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

out vec3 Normal;
out vec4 FragPos;
out mat4 transport_view;
out mat4 transport_transform;

uniform mat4 u_transform;

void main()
{
    FragPos = u_transform * vec4(aPos, 1.0);
    Normal = aNormal;
    transport_view = view;
    transport_transform = u_transform;

    gl_Position = projection * view * FragPos;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

in vec3 Normal;
in vec4 FragPos;
in mat4 transport_view;
in mat4 transport_transform;

layout(std140, binding = 1) uniform Light
{
    mat4 light_property1;
    mat4 light_property2;
};

uniform vec3 u_color;
uniform int u_entity;

void main()
{
    float ambientStrength = light_property1[0][0];
    float specularStrength = light_property1[0][1];
    int specularIndex = int(light_property1[0][2]);
    vec3 lightPos = { light_property1[1][0], light_property1[1][1], light_property1[1][2] };
    vec4 lightColor = { light_property1[2][0], light_property1[2][1], light_property1[2][2], light_property1[2][3] };
    //attenuation
    float constant = light_property1[3][0];
    float mlinear = light_property1[3][1];
    float quadratic = light_property1[3][2];
    //soptlight
    vec3 soptlight_direction = { light_property2[0][0], light_property2[0][1], light_property2[0][2] };
    float spotlight_inner_cutoff = light_property2[1][0];
    float spotlight_outer_cutoff = light_property2[1][1];

    vec4 ambient = ambientStrength * vec4(1.0, 1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - vec3(FragPos));
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec3 viewPos = vec3(transport_view * FragPos);
    vec3 viewNorm = normalize(vec3(transport_view * vec4(Normal,0.0f)));

    vec3 viewDir = normalize(vec3(0, 0, 0) - viewPos);
    vec3 reflectDir = reflect(-lightDir, viewNorm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularIndex);
    vec4 specular = specularStrength * spec * lightColor;

    vec4 result;

    //attenuation
    float distance = length(lightPos - vec3(FragPos));
    float attenuation = 1.0f / (constant + mlinear * distance + quadratic * (distance * distance));
    //spotlight
    //spotlight_direction = vec3(transport_transform * vec4(spotlight_direction, 0.0));
    float theta = dot(lightDir, normalize(-soptlight_direction));  
    float spotlight_intensity = clamp((theta - spotlight_outer_cutoff) / (spotlight_inner_cutoff - spotlight_outer_cutoff), 0.0, 1.0);  //软化边缘
    diffuse *= spotlight_intensity;
    specular *= spotlight_intensity;    //不对ambient做影响
    result = attenuation * (ambient + diffuse + specular) * vec4(u_color, 1.0);

    color0 = result;
    color1 = u_entity;
}
