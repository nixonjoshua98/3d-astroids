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
	vec3 nNormal = normalize(normals);
	
	
	// Light 1
	float lightAmbientStrength = 0.3f;
	vec3 objectAmbientReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
	
	vec3 ambient = (lightAmbientStrength * objectAmbientReflectionCoeff) * lightColour;
	vec3 lightDirection1 = normalize(lightPosition - fragmentPosition);
	float diffuseStrength = max(dot(nNormal, lightDirection1), 0.0f);
	vec3 objectDiffuseReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse = (diffuseStrength * objectDiffuseReflectionCoeff) * lightColour;
	
	
	// Light 2
	float lightAmbientStrength2 = 0.3f;
	vec3 objectAmbientReflectionCoeff2 = vec3(1.0f, 1.0f, 1.0f);
	
	vec3 ambient2 = (lightAmbientStrength2 * objectAmbientReflectionCoeff2) * lightColour2;
	vec3 lightDirection2 = normalize(lightPosition2 - fragmentPosition);
	float diffuseStrength2 = max(dot(nNormal, lightDirection2), 0.0f);
	vec3 objectDiffuseReflectionCoeff2 = vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse2 = (diffuseStrength2 * objectDiffuseReflectionCoeff2) * lightColour2;
	
	// --
	vec4 textureColour = texture(aTex, textureCoordinate);	
	
	// Out	
	vertColour = (vec4((ambient + diffuse + ambient2 + diffuse2),1.0) * (textureColour));	
}