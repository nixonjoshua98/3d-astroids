#include "JN_Model.h"
#include "JN_Shader.h"


JN_Model::JN_Model()
{

}


JN_Model::~JN_Model()
{

}


void JN_Model::SetBuffers()
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		modelData.push_back(vertices[indices[i]].x);
		modelData.push_back(vertices[indices[i]].y);
		modelData.push_back(vertices[indices[i]].z);
		modelData.push_back(texCoords[indices[i + 1]].x);
		modelData.push_back(texCoords[indices[i + 1]].y);
		modelData.push_back(normals[indices[i + 2]].x);
		modelData.push_back(normals[indices[i + 2]].y);
		modelData.push_back(normals[indices[i + 2]].z);
	}

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, modelData.size() * sizeof(modelData[0]), &modelData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void JN_Model::Render()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(vertices));

	glBindVertexArray(0);
}
