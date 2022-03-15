#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_ViewProjection;
out vec2 v_TexCoord;

void main()
{
    gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_TexCoord = texCoord;
}


#shader fragment
#version 330 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}