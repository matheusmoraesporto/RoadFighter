#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdlib.h>
#include "Layer.h"
using namespace std;

Layer layers[3];

void RenderLayer(GLuint vao, GLuint texture, int sp)
{
	//Inicio do código para carregar textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(sp, "basic_texture"), 0);

	//glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(vao);
}

void LoadImage(Layer& l, int id)
{
	const char* img = "";
	float taxaIncremento = 0;

	switch (id)
	{
	case 1:
		img = "..\\Images\\ocean2.jpg";
		taxaIncremento = 1.0f;
		break;
	case 2:
		img = "..\\Images\\street.png";
		taxaIncremento = 0.5f;
		break;
	case 3:
		img = "..\\Images\\cloud.png";
		taxaIncremento = 0.8f;
		break;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(img, &width, &height, &nrChannels, 0);

	if (data)
	{
		nrChannels == 3
			? glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data)
			: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

		l.setHeight(height);
		l.setWidth(width);
		l.setTid(texture);
		l.setId(id);
		l.setScrollRateY(taxaIncremento);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void geometriaLayer(Layer& l)
{
	GLfloat vertices[] = {
		// positions			// texture coords
		0.0f,   600.0f, +0.0f,	  0.0, 0.0f,
		0.0f,   0.0f,   +0.0f,	  0.0f, 1.0f,
		800.0f, 600.0f, +0.0f,	  1.0f, 0.0f,

		800.0f, 600.0f, +0.0f,	  1.0, 0.0f,
		0.0f,   0.0f,   +0.0f,	  0.0f, 1.0f,
		800.0f, 0.0f,   +0.0f,	  1.0f, 1.0f,
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	l.setVao(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
		"	gl_Position = proj * matrix * vec4 (vertex_position, 1.0);"
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
		LoadImage(layers[i], i + 1);

		geometriaLayer(layers[i]);

		glBindVertexArray(layers[i].vao);
	}

	while (!glfwWindowShouldClose(window))
	{
		//glfwPollEvents();
		//const int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		//if (state == GLFW_PRESS) {
		//	double mx, my;
		//	glfwGetCursorPos(window, &mx, &my);
		//	matrix = glm::translate(glm::mat4(1), glm::vec3(mx - WIDTH / 2.0f, my - HEIGHT / 2.0f, 0));
		//}

		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		//	glfwSetWindowShouldClose(window, GLFW_TRUE);
		//}

		glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);

		glUseProgram(shader_programme);
		proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));

		for (size_t i = 0; i < 3; i++)
		{
			RenderLayer(layers[i].vao, layers[i].tid, shader_programme);
			//if (layers[i].id == 1) {
			layers[i].ty -= layers[i].scrollRateY * 0.015f;

			glUniform1f(glGetUniformLocation(shader_programme, "offsety"), layers[i].ty);

			// bind Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, layers[i].tid);
			glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);

			//}
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