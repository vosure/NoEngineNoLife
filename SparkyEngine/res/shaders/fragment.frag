#version 330 core

out vec4 color;

uniform vec2 light_position;

in data
{
	vec4 position;
	vec4 color;
}fragment_in;

void main()
{
	float intensity = 1.0 / length(fragment_in.position.xy - light_position);
	color = fragment_in.color * intensity;
}