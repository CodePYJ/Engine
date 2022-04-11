#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 alocationPos;

out vec3 color;
out vec2 locationPos;

uniform mat4 transform;
uniform mat4 u_ViewProjection;
uniform vec3 u_color;

void main()
{
    gl_Position = u_ViewProjection * transform * vec4(aPos, 1.0);
    color = u_color;
    locationPos = alocationPos;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 color0;
layout(location = 1) out int color1;

uniform int entity;
uniform float thickness;

in vec3 color;
in vec2 locationPos;

void main()
{
    float fade = 0.01;
    float dist = sqrt(dot(locationPos, locationPos));
    if (dist > 1.0 || dist < 1.0 - thickness - fade)
        discard;
    float alpha = 1.0 - smoothstep(1.0f - fade, 1.0f, dist);
    alpha *= smoothstep(1.0 - thickness - fade, 1.0 - thickness, dist);
    color0 = vec4(color,1.0);
    color0.a = vec4(color,1.0).a * alpha;

    color1 = entity;
}
