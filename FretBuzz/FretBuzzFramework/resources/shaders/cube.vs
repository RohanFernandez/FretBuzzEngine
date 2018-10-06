#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;

uniform mat4 u_m4Model;
uniform mat4 u_m4transformation;
uniform mat3 u_m3NormalMatrix;

out vertData
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} outVertexData;

void main()
{
	gl_Position = u_m4transformation * vec4(a_position, 1.0);
	outVertexData.position = vec3(u_m4Model * vec4(a_position, 1.0));
	outVertexData.normal = normalize(u_m3NormalMatrix * a_normal);
	outVertexData.texCoords = a_texCoords;
}