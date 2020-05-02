#include "GameObject.h"

GameObject::GameObject()
{
}

void GameObject::nextFrame()
{
}

void GameObject::setVao(GLuint value)
{
	this->vao = value;
}

void GameObject::setId(int value)
{
	this->id = value;
}

void GameObject::setTid(GLuint value)
{
	this->tid = value;
}