#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_v4LightColor;
uniform float u_fAmbientStrength;

uniform vec3 u_v3LightPosition;
uniform vec3 u_v3CamPosition;

in vertData
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} inVertexData;

uniform sampler2D texSampler;

void main()
{
	vec3 l_v3LightDirection = normalize(inVertexData.position - u_v3LightPosition);
	vec3 l_v3ViewDirection = normalize(inVertexData.position - u_v3CamPosition);

	float l_fDiffuseColor = max(0.0, dot(inVertexData.normal, -l_v3LightDirection)) * 0.5;
	float l_fSpecularColor = pow(max(0.0, dot(-l_v3ViewDirection,reflect(l_v3LightDirection, inVertexData.normal))), 32);
	
	color = (texture(texSampler, inVertexData.texCoords)) * u_v4LightColor * (u_fAmbientStrength + l_fDiffuseColor + l_fSpecularColor);
}