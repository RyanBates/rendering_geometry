#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Colour;
layout(location = 2) in vec4 Normal;

out vec4 vPosition;
out vec4 vNormal;
out vec4 vColour;

uniform mat4 projectionViewWorldMatrix;

void main() 
{ 	

	gl_Position = projectionViewWorldMatrix * Position;

	vNormal = Normal;
	vPosition = Position;
	vColour = Colour;	
}