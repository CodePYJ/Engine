#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * transform * vec4(aPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;

void main()
{
    FragColor = lightColor;

}