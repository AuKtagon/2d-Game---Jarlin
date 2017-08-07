#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


class Camera
{
public:
	void Render(GLuint program, glm::vec3 trans);

private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 world;

	int WIDTH = 1000;
	int HEIGHT = 1000;
};

