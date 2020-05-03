#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdlib.h>
#include "Layer.h"
#include "GameObject.h"
using namespace std;

Layer layers[3];
GameObject sprites[4];

void Render(GLuint vao, GLuint texture, int sp)
{
	//Inicio do código para carregar textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(sp, "basic_texture"), 0);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(vao);
}

void LoadImage(Layer& l, GameObject& go, int id, bool isSprite)
{
	const char* img = "";
	float taxaIncremento = 0;
	float valueZ = 0;
	char name;

	switch (id)
	{
	case 1:
		img = "..\\Images\\ocean.jpg";
		taxaIncremento = 1.0f;
		valueZ = 1.0f;
		break;
	case 2:
		img = "..\\Images\\street.png";
		taxaIncremento = 0.5f;
		valueZ = 1.001f;
		break;
	case 3:
		img = "..\\Images\\cloud.png";
		taxaIncremento = 0.8f;
		valueZ = 0.9f;
		break;
	case 4:
		img = "..\\Images\\player.png";
		valueZ = 1.0f;
		break;
	case 5:
		img = "..\\Images\\enemyRed.png";
		valueZ = 1.0f;
		break;
	case 6:
		img = "..\\Images\\enemyWhite.png";
		valueZ = 1.0f;
		break;
	case 7:
		img = "..\\Images\\enemyYellow.png";
		break;
	case 8:
		img = "..\\Images\\youWin.PNG";
		break;
	case 9:
		img = "..\\Images\\gameOver.PNG";
		break;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (isSprite)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(img, &width, &height, &nrChannels, 0);

	if (data)
	{
		nrChannels == 3
			? glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data)
			: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

		if (isSprite)
		{
			go.setTid(texture);
			go.setId(id);
		}
		else
		{
			l.setHeight(height);
			l.setWidth(width);
			l.setTid(texture);
			l.setId(id);
			l.setScrollRateY(taxaIncremento);
			l.setZ(valueZ);
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void DefineGeometry(Layer& l, GameObject& go, bool isSprite)
{
	GLfloat verticesLayer[] = {
		// positions			  // texture coords
		0.0f,   600.0f, +0.0f,	  0.0, 0.0f,
		0.0f,   0.0f,   +0.0f,	  0.0f, 1.0f,
		800.0f, 600.0f, +0.0f,	  1.0f, 0.0f,

		800.0f, 600.0f, +0.0f,	  1.0, 0.0f,
		0.0f,   0.0f,   +0.0f,	  0.0f, 1.0f,
		800.0f, 0.0f,   +0.0f,	  1.0f, 1.0f,
	};

	GLfloat verticesSpriteEnemyWhite[] = {
		// positions			  // texture coords
		150.0f, -300.0f, +0.0f,	  0.0, 0.0f,
		150.0f, -150.0f, +0.0f,	  0.0f, 1.0f,
		250.0f, -300.0f, +0.0f,	  1.0f, 0.0f,

		250.0f, -300.0f, +0.0f,	  1.0, 0.0f,
		150.0f, -150.0f, +0.0f,	  0.0f, 1.0f,
		250.0f, -150.0f, +0.0f,	  1.0f, 1.0f,
	};

	GLfloat verticesSpriteEnemyRed[] = {
		// positions			  // texture coords
		550.0f, -650.0f, +0.0f,	  0.0, 0.0f,
		550.0f, -500.0f, +0.0f,	  0.0f, 1.0f,
		650.0f, -650.0f, +0.0f,	  1.0f, 0.0f,

		650.0f, -650.0f, +0.0f,	  1.0, 0.0f,
		550.0f, -500.0f, +0.0f,	  0.0f, 1.0f,
		650.0f, -500.0f, +0.0f,	  1.0f, 1.0f,
	};

	GLfloat verticesSpriteEnemyYellow[] = {
		// positions			  // texture coords
		350.0f, -500.0f, +0.0f,	  0.0, 0.0f,
		350.0f, -350.0f, +0.0f,	  0.0f, 1.0f,
		450.0f, -500.0f, +0.0f,	  1.0f, 0.0f,

		450.0f, -500.0f, +0.0f,	  1.0, 0.0f,
		350.0f, -350.0f, +0.0f,	  0.0f, 1.0f,
		450.0f, -350.0f, +0.0f,	  1.0f, 1.0f,
	};

	GLfloat verticesSpritePlayer[] = {
		// positions			  // texture coords
		300.0f, 550.0f, +0.0f,	  0.0, 0.0f,
		300.0f, 400.0f, +0.0f,	  0.0f, 1.0f,
		450.0f, 550.0f, +0.0f,	  1.0f, 0.0f,

		450.0f, 550.0f, +0.0f,	  1.0, 0.0f,
		300.0f, 400.0f, +0.0f,	  0.0f, 1.0f,
		450.0f, 400.0f, +0.0f,	  1.0f, 1.0f,
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	isSprite ? go.setVao(VAO) : l.setVao(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (go.id == 4)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSpritePlayer), verticesSpritePlayer, GL_STATIC_DRAW);
	}
	else if (go.id == 5)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSpriteEnemyRed), verticesSpriteEnemyRed, GL_STATIC_DRAW);
	}
	else if (go.id == 6)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSpriteEnemyWhite), verticesSpriteEnemyWhite, GL_STATIC_DRAW);
	}
	else if (go.id == 7)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSpriteEnemyYellow), verticesSpriteEnemyYellow, GL_STATIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLayer), verticesLayer, GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void DefineOffsetAndRender(int sp, float offsetx, float offsety, float z, GLuint vao, GLuint tid)
{
	glUniform1f(glGetUniformLocation(sp, "offsetx"), offsetx);
	glUniform1f(glGetUniformLocation(sp, "offsety"), offsety);
	glUniform1f(glGetUniformLocation(sp, "layer_z"), z);

	Render(vao, tid, sp);
}

void Transform(glm::mat4& mt, unsigned int& tl, int sp, float x, float y, float z)
{
	mt = glm::mat4(1.0f);
	mt = glm::translate(mt, glm::vec3(x, y, z));
	tl = glGetUniformLocation(sp, "matrix");
	glUniformMatrix4fv(tl, 1, GL_FALSE, glm::value_ptr(mt));
}

void ResetData(float& goDown, int& outdatedCars, float& moveLeftRight, bool isGameOver)
{
	goDown = -300.0f;
	outdatedCars++;

	if (isGameOver)
	{
		outdatedCars = 0;
		moveLeftRight = 0.0f;
	}
}

void StartGame(GLFWwindow* window)
{
	//Vertex da textura
	const char* vertex_shader =
		"#version 410\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec2 texture_mapping;"
		"uniform mat4 proj;"
		"uniform mat4 matrix;"
		"out vec2 texture_coordinates;"
		"uniform float layer_z;"
		"void main() {"
		"	texture_coordinates = vec2( texture_mapping.x, 1.0 - texture_mapping.y );"
		"	gl_Position = proj * matrix * vec4 (vertex_position, layer_z);"
		"}";

	//Fragment da textura
	const char* fragment_shader =
		"#version 410\n"
		"in vec2 texture_coordinates;"
		"uniform sampler2D basic_texture;"
		"uniform float offsetx;"
		"uniform float offsety;"
		"out vec4 frag_color;"
		"void main() {"
		" vec4 texel = texture(basic_texture, vec2(texture_coordinates.x + offsetx, texture_coordinates.y + offsety));"
		" if (texel.a < 0.5) "
		"	discard; "
		" frag_color = texel;"
		"}";

	int WIDTH = 800;
	int HEIGHT = 600;

	glm::mat4 proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
	glm::mat4 matrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

	// identifica vs e o associa com vertex_shader
	int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	// identifica fs e o associa com fragment_shader
	int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	// identifica do programa, adiciona partes e faz "linkagem"
	int shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	for (size_t i = 0; i < 3; i++)
	{
		LoadImage(layers[i], GameObject::GameObject(), i + 1, false);

		DefineGeometry(layers[i], GameObject::GameObject(), false);

		glBindVertexArray(layers[i].vao);
	}

	for (size_t j = 0; j < 4; j++)
	{
		LoadImage(Layer::Layer(), sprites[j], j + 4, true);

		DefineGeometry(Layer::Layer(), sprites[j], true);

		glBindVertexArray(sprites[j].vao);
	}

	GameObject gameOver = GameObject::GameObject();
	LoadImage(Layer::Layer(), gameOver, 9, true);
	DefineGeometry(Layer::Layer(), gameOver, true);
	glBindVertexArray(gameOver.vao);

	GameObject youWin = GameObject::GameObject();
	LoadImage(Layer::Layer(), youWin, 8, true);
	DefineGeometry(Layer::Layer(), youWin, true);
	glBindVertexArray(youWin.vao);

	glm::mat4 matrix2 = glm::mat4(1.0f);
	unsigned int transformloc = glGetUniformLocation(shader_programme, "matrix");
	glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(matrix));
	float goDown = -300;
	float moveLeftRigth = 0.0f;
	bool isGameOver = false;
	int outdatedCars = 0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.8f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);

		glUseProgram(shader_programme);
		proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));

		if (outdatedCars >= 10)
		{
			DefineOffsetAndRender(shader_programme, 0.0f, 0.0f, 1.0f, youWin.vao, youWin.tid);
		}
		else if (isGameOver)
		{
			DefineOffsetAndRender(shader_programme, 0.0f, 0.0f, 1.0f, gameOver.vao, gameOver.tid);
			ResetData(goDown, outdatedCars, moveLeftRigth, true);
		}
		else
		{
			for (size_t i = 0; i < 3; i++)
			{
				layers[i].ty -= layers[i].scrollRateY * 0.015f;

				DefineOffsetAndRender(shader_programme, layers[i].tx, layers[i].ty, layers[i].z, layers[i].vao, layers[i].tid);
			}

			for (size_t i = 0; i < 4; i++)
			{
				if (sprites[i].vao == 4)
				{
					const int moveLeft = glfwGetKey(window, GLFW_KEY_LEFT);
					if (moveLeft == GLFW_PRESS && moveLeftRigth >= -200.0f)
					{
						moveLeftRigth -= 1.0f;
					}

					const int moveRight = glfwGetKey(window, GLFW_KEY_RIGHT);
					if (moveRight == GLFW_PRESS && moveLeftRigth <= 250.0f)
					{
						moveLeftRigth += 1.0f;
					}

					Transform(matrix2, transformloc, shader_programme, moveLeftRigth, 0.0f, 0.0f);
				}

				if (sprites[i].vao > 4)
				{
					Transform(matrix2, transformloc, shader_programme, 0.0f, goDown, 0.0f);
				}

				glUniform1f(glGetUniformLocation(shader_programme, "offsety"), 0);
				DefineOffsetAndRender(shader_programme, 0, 0, 1.0f, sprites[i].vao, sprites[i].tid);
			}

			if (goDown >= 1250.0f)
			{
				ResetData(goDown, outdatedCars, moveLeftRigth, false);
			}
			goDown += 2.0f;
		}

		if (
			(goDown >= 570 && goDown <= 846 && moveLeftRigth <= -85) ||
			(goDown >= 800 && goDown <= 1040 && moveLeftRigth >= -70 && moveLeftRigth <= 120) ||
			(goDown >= 930 && goDown <= 1200 && moveLeftRigth >= 126)
			)
		{
			isGameOver = true;
		}

		const int enter = glfwGetKey(window, GLFW_KEY_ENTER);
		if (enter == GLFW_PRESS)
		{
			outdatedCars = 0;
			isGameOver = false;
		}

		glfwSwapBuffers(window);
	}
}

int main()
{
	// Tratamento para rodar em outros ambientes
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Road Fighter developed by Matheus Moraes Porto", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	StartGame(window);

	// encerra contexto GL e outros recursos da GLFW
	glfwTerminate();
	return 0;
}