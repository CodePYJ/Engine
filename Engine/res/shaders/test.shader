#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 u_ViewProjection;


void main()
{
    gl_Position = u_ViewProjection * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
    FragColor = u_Color;
}