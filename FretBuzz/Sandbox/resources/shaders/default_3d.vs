#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_m4transformation;

void main()
{
	gl_Position = u_m4transformation * vec4(a_position, 1.0);
}