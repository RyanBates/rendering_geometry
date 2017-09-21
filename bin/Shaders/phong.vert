#version 410

layout(location = 0) in vec4 Position;
layout(location = 2) in vec4 Normal;

out vec4 vPosition;
out vec4 vNormal;

uniform mat4 ProjectionViewModel;
uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;

void main() 
{ 
	gl_Position = ProjectionViewModel * Position;
}