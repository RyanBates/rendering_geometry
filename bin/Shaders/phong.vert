#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Colour;
layout(location = 2) in vec4 Normal;
layout(location = 3) in vec2 Uv;

out vec4 vPosition;
out vec4 vNormal;
out vec4 vColour;
out vec2 vUv;

uniform mat4 projectionViewWorldMatrix;

void main() 
{ 
	gl_Position = projectionViewWorldMatrix * Position;
	vPosition = Position;
	vNormal = Normal;
	vColour = Colour;
	vUv = Uv;
}