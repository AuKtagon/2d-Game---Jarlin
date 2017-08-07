#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"

#include "Dependencies\freeglut\glut.h"

// Header Files
#include "Scene.h"

#include <stdlib.h>
#include <time.h>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Scene _Scene;

//******************[AUDIO]******************//

#pragma region AUDIO

// Sounds
FMOD::System* audioMgr;
FMOD::Sound* hitSound;
FMOD::Sound* bgMusic;

bool InitFmod() {
	FMOD_RESULT result;

	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK) return false;

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) return false;

	return true;
}

const bool LoadAudio() {
	FMOD_RESULT result;

	result = audioMgr->createSound("Assets/audio/MenuMusic.mp3", FMOD_DEFAULT, 0, &hitSound);
	result = audioMgr->createSound("Assets/audio/MemeTheme.mp3", FMOD_LOOP_NORMAL, 0, &bgMusic);

	bgMusic->setMode(FMOD_LOOP_NORMAL);

	return true;
}

#pragma endregion

//******************[INPUT]******************//

#pragma region INPUT

// Keyboard
#define BUTTON_UP   0 
#define BUTTON_DOWN 1
unsigned char keyState[255];

void keyboard(unsigned char key, int x, int y) {
	keyState[key] = BUTTON_DOWN;
}

void keyboard_up(unsigned char key, int x, int y) {
	keyState[key] = BUTTON_UP;
}

#pragma endregion

//******************[PROGRAM]******************//

#pragma region PROGRAM

void init() {
	InitFmod();
	LoadAudio();
	FMOD::Channel* channel;
	audioMgr->playSound(bgMusic, 0, false, &channel);

	_Scene.init();	// Main Scene
}

void render(void) {
	_Scene.RenderObject();	// Render Objects
}

void update() {
	glutPostRedisplay(); // Render function


	_Scene.Update(keyState);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
}

#pragma endregion

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 5); glutInitWindowSize(1000, 1000);
	glutCreateWindow("Robotron 9000 - 3D Game - Jarlin");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();
	return (0);
}