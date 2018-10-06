#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec4 m_v4LightVector; // If light.w == 0.0f then its directional else its positional
	
	vec3 m_v3AmbientColor;
	vec3 m_v3Diffuse;
	vec3 m_v3Specular;
};

struct Material
{
	float m_fShininess;
	sampler2D m_texDiffuse;
	sampler2D m_texSpecular;
};

in vertData
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} inVertexData;

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_v3CamPosition;

void main()
{
	vec3 l_v3LightDirection = (u_Light.m_v4LightVector.w == 0.0f) ? normalize(vec3(u_Light.m_v4LightVector)) : normalize(inVertexData.position - vec3(u_Light.m_v4LightVector));
	vec3 l_v3ViewDirection = normalize(inVertexData.position - u_v3CamPosition);

	vec3 l_v3DiffuseSampledColor = vec3(texture(u_Material.m_texDiffuse, inVertexData.texCoords));
	vec3 l_v3SpecularSampledColor = vec3(texture(u_Material.m_texSpecular, inVertexData.texCoords));
	
	vec3 l_v3AmbientColor = u_Light.m_v3AmbientColor * l_v3DiffuseSampledColor;
	vec3 l_v3DiffuseColor = u_Light.m_v3Diffuse * l_v3DiffuseSampledColor * max(0.0, dot(inVertexData.normal, -l_v3LightDirection));
	vec3 l_v3SpecularColor = u_Light.m_v3Specular * l_v3SpecularSampledColor * pow(max(dot(-l_v3ViewDirection, normalize(reflect(l_v3LightDirection, inVertexData.normal))),0.0), u_Material.m_fShininess);
	
	color = vec4(l_v3AmbientColor + l_v3DiffuseColor + l_v3SpecularColor, 1.0);
}