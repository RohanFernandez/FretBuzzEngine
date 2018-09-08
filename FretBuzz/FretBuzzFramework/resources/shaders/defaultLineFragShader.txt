#version 330 core

layout(location = 0) out vec4 color;

in vertData
{
	vec4 position;
	vec4 vertColour;
} inVertexData;

void main()
{
	color = inVertexData.vertColour;
}