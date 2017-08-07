#include "Utils.h"

Utils::Utils()
{
	GLuint vao = NULL;
	GLuint vbo = NULL;
	GLuint ebo = NULL;
};

void Utils::CreateObj(GLfloat passing_vertices, GLuint passing_indices) {
	ShaderLoader ShaderLoader;
	program = ShaderLoader.CreateProgram("VAO_3DGAME.vs", "VAO_3DGAME.fs");

	glEnable(GL_BLEND);	// .png transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Vertices
	for (size_t i = 0; i < vec_vertices.size(); i++) {
		vertices[i] = vec_vertices[i];
	}

	// Indices
	for (size_t i = 0; i < vec_indices.size(); i++) {
		indices[i] = vec_indices[i];
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image =
		SOIL_load_image(imageLoc,	// File name 
			&width,	// Width of the image 
			&height,	// Height of the image
			0,	// number of channels 
			SOIL_LOAD_RGBA);

	std::cout << SOIL_last_result() << ": " << imageLoc << std::endl;

	glTexImage2D(GL_TEXTURE_2D,	// type of texture
		0,	//mipmap level 
		GL_RGBA,	// format of RGB values to be stored 5225
		width,	// width of resulting texture 
		height,	//height of resulting texture 
		0,	//value must be 0 
		GL_RGBA,	// format of the pixel data 
		GL_UNSIGNED_BYTE,	// type of data passed in 
		image);	//pointer to image data in memory

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// VAO
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, //Layout Location on vertex shader
		3, //3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, //data Normalized?
		8 * sizeof(GLfloat), // stide
		(GLvoid*)0); // offset

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(6 * sizeof(GLfloat))); // stride

	glEnableVertexAttribArray(2);
};

void Utils::Render(float x, float y, float z) {
	glUseProgram(program);

	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);	// Delta Time implementation
	//currentTime = currentTime / 1000;
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	// Set value to the parameter
	glUniform1f(currentTimeLocation, currentTime);	// Set value

	// Translation
	glm::vec3 newPositonObj = glm::vec3(x, y, z);	// Translate Movement
	glm::mat4 translation;
	translation = glm::translate(glm::mat4(), newPositonObj);
	//translation = glm::scale(translation, glm::vec3(0.40, 0.40, 0.40));	// **********************

	GLuint transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translation));

	cam.Render(program, newPositonObj);	// Render Camera

	glEnable(GL_DEPTH_TEST);	// DEPTH

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, //Layout Location on vertex shader
		3, //3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, //data Normalized?
		8 * sizeof(GLfloat), // stide
		(GLvoid*)0); // offset

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(6 * sizeof(GLfloat))); // stride

	glEnableVertexAttribArray(2);


	glBindTexture(GL_TEXTURE_2D, texture);	// Rendering Texture
	glBindVertexArray(this->vao); // Bind VAO

	//glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);	// Pyramid
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// Cube

	glBindVertexArray(0);

	glDisable(GL_DEPTH_TEST);	// DEPTH
};

void Utils::SetImage(const char* image)
{
	imageLoc = image;
}

void Utils::SetVert(GLfloat vertices)
{
	vec_vertices.push_back(vertices);
}

void Utils::SetInd(GLuint indices)
{
	vec_indices.push_back(indices);
}