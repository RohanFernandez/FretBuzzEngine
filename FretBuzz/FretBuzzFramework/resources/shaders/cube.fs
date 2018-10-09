#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec4 u_v4LightPosition;
	vec3 u_v3LightDirection;
	vec3 u_v3ConstLinQuad;
	
	vec3 u_v3AmbientColor;
	vec3 u_v3DiffuseColor;
	vec3 u_v3SpecularColor;
	
	float u_fInnerCutOff;
	float u_fOuterCutOff;
	
	float u_fIntensity;
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

uniform Light u_DirectionalLight[1];
uniform Light u_SpotLight[1];
uniform Light u_PointLight[1];

uniform vec3 u_v3CamPosition;

vec3 getDirectionalLightColor(Light a_Light, vec3 a_v3ViewDirection, vec3 a_v3DiffuseSampledColor, vec3 a_v3SpecularSampledColor)
{
	vec3 l_v3LightDirection = (a_Light.u_v4LightPosition.w == 0.0f) ? normalize(a_Light.u_v3LightDirection) : normalize(inVertexData.position - vec3(a_Light.u_v4LightPosition));
	float l_fDistance = length(vec3(a_Light.u_v4LightPosition) - inVertexData.position);
	float l_fAttenuation = 1.0f / (a_Light.u_v3ConstLinQuad.x + a_Light.u_v3ConstLinQuad.y * l_fDistance + a_Light.u_v3ConstLinQuad.z * l_fDistance * l_fDistance);
	
	vec3 l_v3AmbientColor = a_Light.u_v3AmbientColor * a_v3DiffuseSampledColor;
	vec3 l_v3DiffuseColor = a_Light.u_v3DiffuseColor * a_v3DiffuseSampledColor * max(0.0, dot(inVertexData.normal, -l_v3LightDirection));
	vec3 l_v3SpecularColor = a_Light.u_v3SpecularColor * a_v3SpecularSampledColor * pow(max(dot(-a_v3ViewDirection, normalize(reflect(l_v3LightDirection, inVertexData.normal))),0.0), u_Material.m_fShininess);
	
	return vec3((l_v3AmbientColor + l_v3DiffuseColor + l_v3SpecularColor) * l_fAttenuation * a_Light.u_fIntensity);
}

vec3 getSpotLightColor(Light a_Light, vec3 a_v3ViewDirection, vec3 a_v3DiffuseSampledColor, vec3 a_v3SpecularSampledColor)
{
	vec3 l_v3LightToFragDirection = normalize(inVertexData.position - vec3(a_Light.u_v4LightPosition));
	float l_fDistance = length(vec3(a_Light.u_v4LightPosition) - inVertexData.position);
	float l_fAttenuation = 1.0f / (a_Light.u_v3ConstLinQuad.x + a_Light.u_v3ConstLinQuad.y * l_fDistance + a_Light.u_v3ConstLinQuad.z * l_fDistance * l_fDistance);
	
	float l_fLightRayAngle = dot(l_v3LightToFragDirection, a_Light.u_v3LightDirection);
	float l_fSmoothEdge = smoothstep(a_Light.u_fInnerCutOff, a_Light.u_fOuterCutOff, l_fLightRayAngle);
	
	vec3 l_v3AmbientColor = a_Light.u_v3AmbientColor * a_v3DiffuseSampledColor;
	vec3 l_v3DiffuseColor = a_Light.u_v3DiffuseColor * a_v3DiffuseSampledColor * max(0.0, dot(inVertexData.normal, -l_v3LightToFragDirection));
	vec3 l_v3SpecularColor = a_Light.u_v3SpecularColor * a_v3SpecularSampledColor * pow(max(dot(-a_v3ViewDirection, normalize(reflect(l_v3LightToFragDirection, inVertexData.normal))),0.0), u_Material.m_fShininess);
	
	return vec3((l_v3AmbientColor + l_v3DiffuseColor + l_v3SpecularColor) * l_fAttenuation * l_fSmoothEdge * a_Light.u_fIntensity);
}

void main()
{
	vec3 l_v3ViewDirection = normalize(inVertexData.position - u_v3CamPosition);
	vec3 l_v3DiffuseSampledColor = vec3(texture(u_Material.m_texDiffuse, inVertexData.texCoords));
	vec3 l_v3SpecularSampledColor = vec3(texture(u_Material.m_texSpecular, inVertexData.texCoords));
	
	vec3 l_v3FinalLight = vec3(0.0,0.0,0.0);
	//for(int l_iCurrentDirectionalLight = 0; l_iCurrentDirectionalLight < 2; l_iCurrentDirectionalLight++)
	//{
	//	l_v3FinalLight += getDirectionalLightColor(u_DirectionalLight[l_iCurrentDirectionalLight], l_v3ViewDirection, l_v3DiffuseSampledColor, l_v3SpecularSampledColor);
	//}
	//for(int l_iCurrentPointLight = 0; l_iCurrentPointLight < 1; l_iCurrentPointLight++)
	//{
	//	l_v3FinalLight += getDirectionalLightColor(u_PointLight[l_iCurrentPointLight], l_v3ViewDirection, l_v3DiffuseSampledColor, l_v3SpecularSampledColor);
	//}
	for(int l_iCurrentSpotLight = 0; l_iCurrentSpotLight < 1; l_iCurrentSpotLight++)
	{
		l_v3FinalLight += getSpotLightColor(u_SpotLight[l_iCurrentSpotLight], l_v3ViewDirection, l_v3DiffuseSampledColor, l_v3SpecularSampledColor);
	}
	
	color = vec4(l_v3FinalLight, 1.0);
}