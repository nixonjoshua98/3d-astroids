#version 440 core
layout (location = 0) in vec3 Position; //vertex positions
layout (location=1) in vec2 texCoord;	//tex coords
layout (location=2) in vec3 normal;	// vertex normals

 						
out vec2 textureCoordinate;
out vec3 normals;
out vec3 fragmentPosition;

out vec3 lightColour;
out vec3 lightPosition;

out vec3 lightColour2;
out vec3 lightPosition2;

uniform mat4 uNormalMatrix;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

uniform vec3 lightCol;
uniform vec3 lightPos; 

uniform vec3 lightCol2;
uniform vec3 lightPos2;


void main()
{
	gl_Position = uProjection * uView * uModel * vec4(Position.x, Position.y, Position.z, 1.0); 
	
	textureCoordinate = vec2(texCoord.x, 1 - texCoord.y);
	
	fragmentPosition = vec3(uModel * vec4(Position, 1.0f));

	normals = mat3(uNormalMatrix) * normal;
	
	lightColour = lightCol;
	lightPosition = lightPos;
	
	lightColour2 = lightCol2;
	lightPosition2 = lightPos2;
}