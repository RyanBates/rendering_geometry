#version 410

layout(location = 0) in vec4 Position;
layout(location = 3) in vec2 Uv;


out vec4 vPosition;
out vec2 vUv;

uniform sampler2D perlinTexture;

uniform mat4 projectionViewWorldMatrix;

void main() 
{ 	
	vec4 pos = Position;
	pos.y += texture(perlinTexture, Uv).r * 5;

	vPosition = Position;
	vUv = Uv;
	
	gl_Position = projectionViewWorldMatrix * pos;
}