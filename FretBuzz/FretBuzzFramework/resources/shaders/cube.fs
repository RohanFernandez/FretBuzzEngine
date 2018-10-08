#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec4 u_v4LightPosition; // If light.w == 0.0f then its directional else its positional
	vec3 u_v3LightDirection;
	vec3 u_v3ConstLinQuad;
	
	vec3 u_v3AmbientColor;
	vec3 u_v3DiffuseColor;
	vec3 u_v3SpecularColor;
	
	float u_fInnerCutOff;
	float u_fOuterCutOff;
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
uniform Light u_Light[2];
uniform vec3 u_v3CamPosition;

vec3 getLightColor(int a_iLightIndex, vec3 a_v3ViewDirection, vec3 a_v3DiffuseSampledColor, vec3 a_v3SpecularSampledColor)
{
	vec3 l_v3LightDirection = (u_Light[a_iLightIndex].u_v4LightPosition.w == 0.0f) ? normalize(u_Light[a_iLightIndex].u_v3LightDirection) : normalize(inVertexData.position - vec3(u_Light[a_iLightIndex].u_v4LightPosition));
	float l_fDistance = length(vec3(u_Light[a_iLightIndex].u_v4LightPosition) - inVertexData.position);
	float l_fAttenuation = 1.0f / (u_Light[a_iLightIndex].u_v3ConstLinQuad.x + u_Light[a_iLightIndex].u_v3ConstLinQuad.y * l_fDistance + u_Light[a_iLightIndex].u_v3ConstLinQuad.z * l_fDistance * l_fDistance);
	
	vec3 l_v3AmbientColor = u_Light[a_iLightIndex].u_v3AmbientColor * a_v3DiffuseSampledColor;
	vec3 l_v3DiffuseColor = u_Light[a_iLightIndex].u_v3DiffuseColor * a_v3DiffuseSampledColor * max(0.0, dot(inVertexData.normal, -l_v3LightDirection));
	vec3 l_v3SpecularColor = u_Light[a_iLightIndex].u_v3SpecularColor * a_v3SpecularSampledColor * pow(max(dot(-a_v3ViewDirection, normalize(reflect(l_v3LightDirection, inVertexData.normal))),0.0), u_Material.m_fShininess);
	
	return vec3((l_v3AmbientColor + l_v3DiffuseColor + l_v3SpecularColor) * l_fAttenuation);
}

void main()
{
	vec3 l_v3ViewDirection = normalize(inVertexData.position - u_v3CamPosition);
	vec3 l_v3DiffuseSampledColor = vec3(texture(u_Material.m_texDiffuse, inVertexData.texCoords));
	vec3 l_v3SpecularSampledColor = vec3(texture(u_Material.m_texSpecular, inVertexData.texCoords));
	
	vec3 l_v3FinalLight = vec3(0.0,0.0,0.0);
	for(int l_iCurrentLight = 0; l_iCurrentLight < 2; l_iCurrentLight++)
	{
		l_v3FinalLight += getLightColor(l_iCurrentLight, l_v3ViewDirection, l_v3DiffuseSampledColor, l_v3SpecularSampledColor);
	}
	
	color = vec4(l_v3FinalLight, 1.0);
}