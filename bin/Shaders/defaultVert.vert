#version 410

in vec4 Pos;
in vec4 Color;

out vec4 vColour;

uniform mat4 projectionViewWorldMatrix;

void main()
{
vColour = Color; 


gl_Position = projectionViewWorldMatrix * Pos;

}