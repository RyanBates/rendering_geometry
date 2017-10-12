#version 410

//ambient
vec4 Ka;
vec4 Ia;

//diffuse
vec4 Kd;
vec4 Id;

//specular
vec3 Ks;
vec3 Is;


uniform float specularPower;
uniform float red;
uniform float green;
uniform float blue;

uniform float LDX;
uniform float LDY;
uniform float LDZ;

vec3 L; //light direction
vec3 V; // camera view
vec3 R; // reflection ray

uniform vec4 Am; // ambient
uniform vec4 Di; // diffuse
uniform vec4 Sp; // specular
uniform sampler2D sampler;

in vec4 vNormal;
in vec4 vPosition;
in vec4 vColour;
in vec4 vCamPosition;
in vec2 vUv;

out vec4 fragColour;

void main() 
{ 
	float a = dot(vNormal.xyz, vec3(0,1.f,0));
	vec3 hemisphere = .5f * mix(vec3(0,1,0), vec3(0,0,1), a) * .5f;


	///////////////////////////////////////////////////////
	
	//ambient
	Ka = vec4(hemisphere, 1);
	Ia = vec4(1);
	vec4 ambient = Ka * Ia ;
	
	////////////////////////////////////////////////////

	// diffuse
	Kd = vec4(0,0,1,1);
	Id = vec4(1);

	L = normalize(vec3(LDX,LDY,LDZ));
	vec3 N = normalize(vNormal.xyz);

	float LdotN = dot(L, N);


	vec4 diffuse = Kd * LdotN * Id;

	//////////////////////////////////////////////////

	//specular using phong
	Ks = vec3(1);
	Is = vec3(1); 
	vec3 cam = vec3(10, 0, 1);

	//specular not using blinn-phong
	R = reflect(-L, N);
	V = normalize(cam - vPosition.xyz);
	
	float RdotV = dot(R, V);
	float influnce = max(0, RdotV);

	float specularTerm = pow(influnce, specularPower);
	vec3 specular_p = Ks * specularTerm * Is; 

	/////////////////////////////////////////////////

	//specular using blinn-phong
	vec3 H = normalize(L + V);
	float HdotN = dot(H, N);
	float influnces = max(0, HdotN);

	float specularTerms = pow(influnces, specularPower);

	vec3 specular_bp = Ks * (specularTerms) * Is;

	//////////////////////////////////////////////////

	//light called
	
	
	vec4 phong = ambient + diffuse + vec4(specular_p, 1); // phong lighting 


	vec4 blinnPhong = ambient + diffuse + vec4(specular_bp, 1); // binn-phong lighting
	
	fragColour = blinnPhong;
}