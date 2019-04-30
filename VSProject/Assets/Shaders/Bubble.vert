#version 440 core
layout (location=0) in vec3 Position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 normal;
 					

uniform mat4 uNormalMatrix;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

uniform vec3 lightCol1;
uniform vec3 lightPos1; 

uniform vec3 lightCol2;
uniform vec3 lightPos2;

out vec2 textureCoordinate;
out vec3 normals;
out vec3 fragmentPosition;

out vec3 lightColour;
out vec3 lightPosition;

out vec3 lightColour2;
out vec3 lightPosition2;


void main()
{
	gl_Position = uProjection * uView * uModel * vec4(Position.x, Position.y, Position.z, 1.0); 
	
	textureCoordinate = vec2(texCoord.x, 1 - texCoord.y);
	
	fragmentPosition = vec3(uModel * vec4(Position, 1.0f));
	
	normals = normal;

	normals = mat3(uNormalMatrix) * normal;
	
	lightColour = lightCol1;
	lightPosition = lightPos1;
	
	lightColour2 = lightCol2;
	lightPosition2 = lightPos2;
}