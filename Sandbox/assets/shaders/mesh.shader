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
    Normal = vec3(u_transform * vec4(aNormal, 0.0f));
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

struct Light
{
    int lightType;
    float ambientStrength;
    vec3 color;
    vec3 position;

    //parallel light
    vec3 parallelDir;

    //point light
    float constant;
    float mlinear;
    float quadratic;

    //spotlight
    float innerCutoff;
    float outerCutoff;
    vec3 spotlightDir;
};

layout(std140, binding = 1) uniform uLight
{
    int lightCount;
    Light lights[32];
};

uniform vec3 u_color;
uniform int u_entity;
uniform float specularStrength;
uniform int shininess;

vec3 BaseLight(Light light, vec3 normal, vec3 lightDir, vec3 viewDir, vec3 viewNorm)
{
    vec3 ambient = light.ambientStrength * light.color;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 reflectDir = reflect(lightDir, viewNorm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * light.color;
    return ambient + diffuse + specular;
}

vec3 Spotlight(Light light, vec3 normal, vec3 lightDir, vec3 viewDir, vec3 viewNorm)
{
    vec3 ambient = light.ambientStrength * light.color;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 reflectDir = reflect(lightDir, viewNorm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * light.color;

    float theta = dot(lightDir, normalize(-light.spotlightDir));
    float spotlight_intensity = clamp((theta - light.outerCutoff) / (light.innerCutoff - light.outerCutoff), 0.0, 1.0);  //软化边缘
    diffuse *= spotlight_intensity;
    specular *= spotlight_intensity;    //不对ambient做影响

    return ambient + diffuse + specular;
}

void main()
{
    vec3 result;

    vec3 viewPos = vec3(transport_view * FragPos);
    vec3 viewNorm = normalize(vec3(transport_view * vec4(Normal,0.0f)));
    vec3 viewDir = normalize(vec3(0, 0, 0) - viewPos);
    vec3 norm = normalize(Normal);

    for (int i = 0; i < lightCount; i++) {
        vec3 lightDir = normalize(lights[i].position - vec3(FragPos));

        if (lights[i].lightType == 0) {
            result += BaseLight(lights[i], norm, normalize(-1 * lights[i].parallelDir), viewDir, viewNorm);
        }

        else if (lights[i].lightType == 1) {
            float distance = length(lights[i].position - vec3(FragPos));
            float attenuation = 1.0f /
                (lights[i].constant +(lights[i].mlinear * distance) + lights[i].quadratic * (distance * distance));
            result += BaseLight(lights[i], norm, lightDir, viewDir, viewNorm) * attenuation;
        }

        else if (lights[i].lightType == 2) {
            result += Spotlight(lights[i], norm, lightDir, viewDir, viewNorm);
        }
    }

    result *= u_color;

    color0 = vec4(result, 1.0f);
    color1 = u_entity;
}
