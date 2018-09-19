#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;

uniform mat4 u_m4transformation;

out vertData
{
	vec3 position;
	vec2 texCoords;
} outVertexData;

void main()
{
	gl_Position = u_m4transformation * vec4(a_position, 1.0) ;
	outVertexData.position = a_position;
	outVertexData.texCoords = a_texCoords;
}