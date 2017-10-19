#version 410

layout(location=0) in vec4 Pos;
layout(location=1) in vec4 Color;

out vec4 vColour;

uniform mat4 projectionViewWorldMatrix;

void main()
{
vColour = Color; 

gl_Position = projectionViewWorldMatrix * Pos;

}