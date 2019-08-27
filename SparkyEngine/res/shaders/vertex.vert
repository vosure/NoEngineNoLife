#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection;

out data
{
	vec4 position;
	vec4 color;
} vertex_out;

void main()
{
	gl_Position = projection * view * model * position;
	vertex_out.position = model * position;
	vertex_out.color = color;
}