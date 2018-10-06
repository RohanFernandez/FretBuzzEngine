#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec3 m_v3LightPosition;
	
	vec3 m_v3AmbientColor;
	vec3 m_v3Diffuse;
	vec3 m_v3Specular;
};

struct Material
{
	float m_fShininess;

	vec3 m_v3Ambient;
	vec3 m_v3Diffuse;
	vec3 m_v3Specular;
};

in vertData
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} inVertexData;

uniform sampler2D texSampler;
uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_v3CamPosition;

void main()
{
	vec3 l_v3LightDirection = normalize(inVertexData.position - u_Light.m_v3LightPosition);
	vec3 l_v3ViewDirection = normalize(inVertexData.position - u_v3CamPosition);

	vec3 l_v3AmbientColor = u_Light.m_v3AmbientColor * u_Material.m_v3Ambient;
	vec3 l_v3DiffuseColor = u_Light.m_v3Diffuse * u_Material.m_v3Diffuse * max(0.0, dot(inVertexData.normal, -l_v3LightDirection));
	vec3 l_v3SpecularColor = u_Light.m_v3Specular * u_Material.m_v3Specular * pow(max(0.0, dot(-l_v3ViewDirection,reflect(l_v3LightDirection, inVertexData.normal))), u_Material.m_fShininess);
	
	color = vec4(l_v3AmbientColor + l_v3DiffuseColor + l_v3SpecularColor, 1.0);
}