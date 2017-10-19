#version 410

uniform sampler2D perlinTexture;

in vec2 vUv;

out vec4 fragColour;

void main() 
{ 	
	fragColour = texture(perlinTexture, vUv).brra;	
}

