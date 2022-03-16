#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 mColor;

uniform mat4 transform;
uniform mat4 u_ViewProjection;

out vec4 aColor;
out vec2 v_TexCoord;

void main()
{
    gl_Position = transform * u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_TexCoord = texCoord;
    aColor = vec4(mColor, 1.0);
}


#shader fragment
#version 330 core

in vec4 aColor;
in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = u_Color;
}