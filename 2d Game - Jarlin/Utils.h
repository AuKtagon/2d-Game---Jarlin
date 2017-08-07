#ifndef UTILS_H
#define UTILS_H

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"

#include "ShaderLoader.h"
#include "Camera.h"
#include <vector>

#include <string>

#include <stdlib.h>    
#include <time.h>  

//******************[Utils Class]******************//

class Utils
{
public:
	// Delta Time
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	Utils();

	void Render(float x, float y, float z);
	void CreateObj(GLfloat vertices, GLuint indices);

	void SetVert(GLfloat vertices);
	void SetInd(GLuint indices);
	void SetImage(const char* image);

private:
	Camera cam;

	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;

	GLuint indices[100];
	GLfloat vertices[500];

	float camerafront = 0.01f;

	const char* imageLoc;

	std::vector<GLfloat> vec_vertices;
	std::vector<GLint> vec_indices;

	GLfloat m_vertices;
	GLuint m_indices;
};

#endif // !ULTILS_H