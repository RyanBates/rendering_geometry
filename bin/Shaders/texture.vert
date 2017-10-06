#version 410

layout(location = 0) in vec4 Position;
layout(location = 3) in vec2 Uv;

out vec4 vPosition;
out vec2 vUv;

uniform sampler2D perlinTexture;

uniform mat4 projectionViewWorldMatrix;

void main() 
{ 	
	vPosition = Position * projectionViewWorldMatrix;

	vPosition.x += texture(perlinTexture, Uv).r * (5 / 5);
	vPosition.y += texture(perlinTexture, Uv).r * (5 / 3);
	vPosition.z += texture(perlinTexture, Uv).r * (5 / 5);
	
	vUv = Uv;

	gl_Position = vPosition;
}