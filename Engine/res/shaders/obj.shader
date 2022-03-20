#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 u_ViewProjection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = u_ViewProjection * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Normal = aNormal;
    FragPos = vec3(transform * vec4(aPos, 1.0));
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.3;
    vec4 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    float specularStrength = 0.3;
    vec3 viewDir = normalize(vec3(0, 0, 0) - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 50);
    vec4 specular = specularStrength * spec * lightColor;

    vec4 result = (diffuse + ambient + specular) * objectColor;
    //vec4 result = ambient;
    FragColor = result;
}