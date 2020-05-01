#include "Layer.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include <glm\detail\type_mat.hpp>
#include <glm\gtc\matrix_transform.hpp>

Layer::Layer()
{
}

Layer::Layer(int widthValue, int heightValue, int tidValue)
{
	setTid(tidValue);
	setHeight(heightValue);
	setWidth(widthValue);
	setTx(0);// ++scrollRate
	setTy(0);
	setScrollRateX(0);// taxa de increm. 
	setScrollRateY(0.1);
}

//void scroll(glm::mat4& matrix)
//{
//	static double previousSeconds = glfwGetTime();
//	double currentSeconds = glfwGetTime();
//	double elapsedSeconds = currentSeconds - previousSeconds;
//
//	previousSeconds = currentSeconds;
//
//	//if (fabs(tx) > 0.5f)
//	//{
//	//	scrolRateX = scrolRateX;
//	//}
//
//	float value = this->ty + scrolRateY / 2.0f;
//	matrix = glm::translate(glm::mat4(1), glm::vec3(0, value, 0));
//}

#pragma region Setters

void Layer::setTid(GLuint value)
{
	this->tid = value;
}

void Layer::setId(int value)
{
	this->id = value;
}

void Layer::setWidth(int value)
{
	this->width = value;
}

void Layer::setHeight(int value)
{
	this->height = value;
}

void Layer::setTx(float value)
{
	this->tx = value;
}

void Layer::setTy(float value)
{
	this->ty = value;
}

void Layer::setScrollRateX(float value)
{
	this->scrollRateX = value;
}

void Layer::setScrollRateY(float value)
{
	this->scrollRateY = value;
}

void Layer::setVao(GLuint value)
{
	this->vao = value;
}

#pragma endregion