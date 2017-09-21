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

uniform vec3 L;
uniform vec3 V;

in vec4 vNormal;
in vec4 vPosition;
out vec4 fragColour;

float dot(vec3 a, vec3 b)
{
	dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z); // d = dot

	return d;
}


void main() 
{ 

	//ambient
	Ka = new vec3();
	Ia = new vec3();
	vec3 ambient = Ka * Ia;


	// diffuse
	Kd = new vec3();
	what = dot(L, vNormal);
	vec3 diffuse = Kd * what;


	//specular not using blinn-phong
	Ks = new vec3();
	later = dot()
	
	vec3 specular_p =Ks * later * Is 


	//specular using blinn-phong

	vec3 spcular_bp = 

	//light called
	FragColor = (ambient, 1);
}