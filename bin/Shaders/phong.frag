#version 410

//ambient
uniform vec3 Ka;
uniform vec3 Ia;

//diffuse
uniform vec3 Kd;
uniform vec3 Id;

//specular
uniform vec3 Ks;
uniform vec3 Is;
uniform float specularPower;

uniform vec3 L; //light direction
uniform vec3 V; // camera view
uniform vec3 R; // reflection ray

in vec4 vNormal;
in vec4 vPosition;
out vec4 fragColour;

float dot(vec3 a, vec3 b)
{
	dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z); // d = dot
}

void main() 
{ 

	//ambient
	Ka = new vec3(0);
	Ia = new vec3(0);
	vec3 ambient = Ka * Ia;


	// diffuse
	Kd = new vec3(0);

	float LdotN = dot(L, vNormal);

	vec3 diffuse = Kd * LdotN;


	//specular not using blinn-phong
	Ks = new vec3(0);

	specularPower = 10;

	flaot RdotV = dot(R, V);
	
	vec3 specular_p = Ks * (RdotV * specularPower) * Is; 


	//specular using blinn-phong
	float bp = dot(L, V);

	vec3 spcular_bp = Ks * (bp * specularPower) * Is;

	//light called
	FragColor = (ambient, 1);
}