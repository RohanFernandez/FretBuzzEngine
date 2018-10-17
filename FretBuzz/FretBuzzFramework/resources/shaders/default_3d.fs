#version 330 core

layout(location = 0) out vec4 color;

struct Material
{
	vec4 u_v4Albedo;
};

uniform Material u_Material;

void main()
{
	color = u_Material.u_v4Albedo;
}