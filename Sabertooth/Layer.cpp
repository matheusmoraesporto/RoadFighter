#include "Layer.h"

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

void Layer::scroll(bool go)
{

}

#pragma region Setters

void Layer::setTid(GLuint value)
{
	this->tid = value;
}

void Layer::setWidth(int value)
{
	this->width = value;
}

void Layer::setHeight(int value)
{
	this->height = value;
}

void Layer::setTx(int value)
{
	this->tx = value;
}

void Layer::setTy(int value)
{
	this->ty = value;
}

void Layer::setScrollRateX(int value)
{
	this->scrolRateX = value;
}

void Layer::setScrollRateY(int value)
{
	this->scrolRateY = value;
}

void Layer::setVao(GLuint value)
{
	this->vao = value;
}

#pragma endregion