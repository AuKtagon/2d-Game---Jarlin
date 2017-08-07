#include "Camera.h"
#include "Dependencies\glm\glm.hpp"

#define BUTTON_UP 0
#define BUTTON_DOWN 1

void Camera::Render(GLuint program , glm::vec3 trans) {
	glm::vec3 cameraPos = glm::vec3(0.0f, 6.0f, 8.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, -0.5f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 newPositon = glm::vec3(0.0f, 0.0f, 0.0f);
	world = glm::translate(glm::mat4(), newPositon);

	GLfloat radius = 4.0f;	// Circle radius of scene
	GLfloat camX = sin(glutGet(GLUT_ELAPSED_TIME)) * radius;
	GLfloat camZ = cos(glutGet(GLUT_ELAPSED_TIME)) * radius;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);	// (Location, Looking at, Y Axis)
	model = glm::translate(glm::mat4(), trans) * glm::rotate(glm::mat4(), -0.0f / 100, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 0.0f / 100, glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);	// Perspective Camera (FOV, Aspect Ratio, Near Plane, Far Plane)

	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint worldLoc = glGetUniformLocation(program, "world");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
}