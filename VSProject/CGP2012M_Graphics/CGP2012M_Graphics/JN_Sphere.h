#pragma once

#include "JN_Model.h"
#include "JN_GameObject.h"
#include "JN_Texture.h"

class JN_Sphere : public JN_GameObject
{
public:
	JN_Sphere(std::string, glm::vec3&, glm::vec3&, glm::mat4&, glm::mat4&);
	~JN_Sphere();

	void Update() override;
	void Render() override;

private:
	JN_Model model;
	JN_Texture texture;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	void LoadModelObj();
	void SetUniforms();
};

