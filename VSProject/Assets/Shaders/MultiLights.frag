#version 440 core

out vec4 vertColour;

in vec2 textureCoordinate;
in vec3 normals;
in vec3 fragmentPosition;

in vec3 lightColour;
in vec3 lightPosition;

in vec3 lightColour2;
in vec3 lightPosition2;

uniform sampler2D aTex;

void main()
{
	float lightAmbientStrength = 0.2f;
	vec3 objectAmbientReflectionCoeff = vec3(0.6f, 0.3f, 0.3f);
	
	vec3 ambient = (lightAmbientStrength * objectAmbientReflectionCoeff) * lightColour;
	
	vec3 nNormal = normalize(normals);
		
	vec3 lightDirection1 = normalize(lightPosition - fragmentPosition);
	vec3 lightDirection2 = normalize(lightPosition2 - fragmentPosition);	
	
	float diffuseStrength = max(dot(nNormal, lightDirection1), 0.0f);
	
	vec3 objectDiffuseReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse = (diffuseStrength * objectDiffuseReflectionCoeff) * lightColour;
	
	vec4 textureColour = texture(aTex, textureCoordinate);	
	
	vertColour = (vec4((ambient+diffuse),1.0) * (textureColour));	
}