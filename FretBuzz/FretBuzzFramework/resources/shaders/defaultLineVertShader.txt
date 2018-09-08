#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_vertColour;

out vertData
{
	vec4 position;
	vec4 vertColour;
} outVertexData;

void main()
{
	gl_Position = vec4(a_position.xy, int(a_position.z), a_position.w) ;
	outVertexData.position = a_position;
	outVertexData.vertColour = a_vertColour;
}