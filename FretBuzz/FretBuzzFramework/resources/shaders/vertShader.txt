#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_vertColour;
layout(location = 2) in vec2 a_texCoords;
layout(location = 3) in float a_texID;

out vertData
{
	vec4 position;
	vec4 vertColour;
	vec2 texCoords;
	float texID;
} outVertexData;

void main()
{
	gl_Position = vec4(a_position.xy, int(a_position.z), a_position.w) ;
	outVertexData.position = a_position;
	outVertexData.texCoords = a_texCoords;
	outVertexData.vertColour = a_vertColour;
	outVertexData.texID = a_texID;
}