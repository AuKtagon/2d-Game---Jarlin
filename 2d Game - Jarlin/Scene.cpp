#include "Scene.h"

#define BUTTON_UP   0 
#define BUTTON_DOWN 1

void Scene::init() {
	srand(time(NULL));

	xGrid = 0.0;
	yGrid = 0.0;
	zGrid = 0.0;

	xEnemy = 0.0;
	yEnemy = 0.5;
	zEnemy = 0.0;

	xPlayer = 0.0;
	yPlayer = 0.5;
	zPlayer = 0.0;

	scoreLabel = new TextLabel("ScoreText", "Assets/fonts/arial.ttf");	// Loading Font
	scoreLabel->setPosition(glm::vec2(10.0f, 10.0f));	// Set score text position
	scoreLabel->setColor(glm::vec3(1.0, 1.0f, 1.0f));	// Set score text color
	scoreLabel->setScale(0.5f);	// Set score scale/size

	livesLabel = new TextLabel("LivesText", "Assets/fonts/arial.ttf");	// Loading Font
	livesLabel->setPosition(glm::vec2(500.0f, 10.0f));	// Set lives text position
	livesLabel->setColor(glm::vec3(1.0, 1.0f, 1.0f));	// Set lives text color
	livesLabel->setScale(0.5f);	// Set score scale/size

	fpsLabel = new TextLabel("FPSText", "Assets/fonts/arial.ttf");	// Loading Font
	fpsLabel->setPosition(glm::vec2(10.0f, 570.0f));	// Set lives text position
	fpsLabel->setColor(glm::vec3(1.0, 1.0f, 1.0f));	// Set lives text color
	fpsLabel->setScale(0.5f);	// Set score scale/size

	grid.SetImage("Assets/images/grid1.png");
	SetGridObject();

	enemy.SetImage("Assets/images/enemy1.png");
	SetEnemyObject();

	object.SetImage("Assets/images/player1.png");
	SetPlayerObject();
}

void Scene::RenderObject() {
	glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);	// .png transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);	// DEPTH

	// Render Objects
	std::cout << xPlayer << " | " << yPlayer << " | " << zPlayer << std::endl;
	grid.Render(xGrid, yGrid, zGrid);	// Render Grid
	enemy.Render(xEnemy, yEnemy, zEnemy);	// Render Enemy
	object.Render(xPlayer, yPlayer, zPlayer);	// Render Player


	for (size_t i = 0; i < gridObject.size(); i++) {	// Grid Object
		gridObject[i].object.Render(gridObject[i].xObject, gridObject[i].yObject, playerObject[i].zObject);
	}

	for (size_t i = 0; i < enemyObject.size(); i++) {	// Enemy Object
		enemyObject[i].object.Render(enemyObject[i].xObject, enemyObject[i].yObject, enemyObject[i].zObject);
	}

	for (size_t i = 0; i < playerObject.size(); i++) {	// Player Object
		playerObject[i].object.Render(playerObject[i].xObject, playerObject[i].yObject, playerObject[i].zObject);
	}

	// Render Text
	scoreLabel->TextRender();	// Render Text [Score]
	livesLabel->TextRender();	// Render Text [Lives]
	fpsLabel->TextRender();	// Render Text [FPS]

	glutSwapBuffers();
}

void Scene::Update(unsigned char *keyState) {
	// Update Delta Time
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	speed = 0.0010 * deltaTime;

	if ((xPlayer + 0.5) > (xEnemy - 0.5) &&	// COLLISION WITH ENEMY
		(xPlayer - 0.5) < (xEnemy + 0.5) &&
		(zPlayer + 0.5) < (zEnemy - 0.5) &&
		(zPlayer - 0.5) > (zEnemy + 0.5)) {
		score -= 100;
		lives -= 1;
	}

	// Text
	std::string currentScore = "Score: ";	// Score text
	score += deltaTime / 10 * 1;
	currentScore += std::to_string(score).c_str();
	scoreLabel->setText(currentScore.c_str());

	std::string currentLives = "Lives: ";	// Lives text
	currentLives += std::to_string(lives).c_str();
	livesLabel->setText(currentLives.c_str());

	std::string fpsCounter = "Restart = 'R'    FPS: ";	// Lives text
	fps = ((1 / deltaTime) * 1000);	// FPS Equation
	fpsCounter += std::to_string(fps).c_str();
	fpsLabel->setText(fpsCounter.c_str());

	KeyInput(keyState);
}

void Scene::SetGridObject() {
	// Cube
	GLfloat vertices[] = {
		//position				//color				//texture coord
		-3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		3.25f, -0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		3.25f, 0.25f, -3.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		3.25f, 0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		3.25f, -0.25f, 3.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};

	for (int i = 0; i < sizeof(vertices) / 4; i++) {
		grid.SetVert(vertices[i]);
	}

	for (int i = 0; i < sizeof(indices) / 4; i++) {
		grid.SetInd(indices[i]);
	}

	grid.CreateObj(*vertices, *indices);
};

void Scene::SetPlayerObject() {
	// Cube
	GLfloat vertices[] = {
		//position				//color				//texture coord
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};

	for (int i = 0; i < sizeof(vertices) / 4; i++) {
		object.SetVert(vertices[i]);
	}

	for (int i = 0; i < sizeof(indices) / 4; i++) {
		object.SetInd(indices[i]);
	}

	object.CreateObj(*vertices, *indices);
};

void Scene::SetEnemyObject() {
	// Cube
	GLfloat vertices[] = {
		//position				//color				//texture coord
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};

	for (int i = 0; i < sizeof(vertices) / 4; i++) {
		enemy.SetVert(vertices[i]);
	}

	for (int i = 0; i < sizeof(indices) / 4; i++) {
		enemy.SetInd(indices[i]);
	}

	enemy.CreateObj(*vertices, *indices);
};

void Scene::KeyInput(unsigned char *keyState) {
	// Keyboard Input
	if (keyState[(unsigned char)'w'] == BUTTON_DOWN && zPlayer > -3.0 || keyState[(unsigned char)'W'] == BUTTON_DOWN && zPlayer > -3.0) {
		zPlayer -= speed;
	}
	if (keyState[(unsigned char)'s'] == BUTTON_DOWN && zPlayer < 3.0 || keyState[(unsigned char)'S'] == BUTTON_DOWN && zPlayer < 3.0) {
		zPlayer += speed;
	}
	if (keyState[(unsigned char)'a'] == BUTTON_DOWN && xPlayer > -3.0 || keyState[(unsigned char)'A'] == BUTTON_DOWN && xPlayer > -3.0) {
		xPlayer -= speed;
	}
	if (keyState[(unsigned char)'d'] == BUTTON_DOWN && xPlayer < 3.0 || keyState[(unsigned char)'D'] == BUTTON_DOWN && xPlayer < 3.0) {
		xPlayer += speed;
	}
	if (keyState[(unsigned char)'q'] == BUTTON_DOWN || keyState[(unsigned char)'Q'] == BUTTON_DOWN) { 
		yPlayer -= speed;
	}
	if (keyState[(unsigned char)'e'] == BUTTON_DOWN || keyState[(unsigned char)'E'] == BUTTON_DOWN) { 
		yPlayer += speed;
	}

	// Restart
	if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN) {
		init();
	}
}