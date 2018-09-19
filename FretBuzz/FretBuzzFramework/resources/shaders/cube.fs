#version 330 core

layout(location = 0) out vec4 color;

in vertData
{
	vec3 position;
	vec2 texCoords;
} inVertexData;

uniform sampler2D texSampler;

void main()
{
	color = texture(texSampler, inVertexData.texCoords);
}