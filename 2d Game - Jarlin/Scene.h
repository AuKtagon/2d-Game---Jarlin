#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\FMOD\fmod.hpp"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "ShaderLoader.h"
#include "Utils.h"
#include "TextLabel.h"
#include "Camera.h"

#include <stdlib.h>    
#include <time.h>   // for random
#include <random>

#define PI 3.14159

struct objectStruct	// *************
{
	Utils object;

	float xObject, yObject, zObject;
};

class Scene
{
public:
	TextLabel* scoreLabel;	// Score Text
	TextLabel* livesLabel;	// Lives Text
	TextLabel* fpsLabel;	// Lives Text
	int score = 0;
	int lives = 3;
	int fps = 0;

	//Scene();
	//~Scene();

	void init();

	void SetGridObject();
	void SetPlayerObject();
	void SetEnemyObject();

	void RenderObject();

	void KeyInput(unsigned char *keyState);
	void Update(unsigned char *keyState);

private:
	// Delta Time;
	float deltaTime;
	float lastFrame = 0.0f;
	float currentFrame = glutGet(GLUT_ELAPSED_TIME);

	unsigned char keyState[255];
	GLfloat speed;

	std::vector<objectStruct> gridObject;
	std::vector<objectStruct> playerObject;
	std::vector<objectStruct> enemyObject;

	Camera cam;

	Utils grid;
	Utils object;
	Utils enemy;

	// Object and Movement
	GLfloat xGrid, yGrid, zGrid;
	GLfloat xPlayer, yPlayer, zPlayer;
	GLfloat xEnemy, yEnemy, zEnemy;
};