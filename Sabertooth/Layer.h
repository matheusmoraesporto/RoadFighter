#pragma once
#include <GL\glew.h>
class Layer
{
public:
	Layer();
	Layer(int widthValue, int heightValue, int tidValue);
	void scroll(bool go);
	void setTid(GLuint value);
	void setWidth(int value);
	void setHeight(int value);
	void setTx(int value);
	void setTy(int value);
	void setScrollRateX(int value);
	void setScrollRateY(int value);
	void setVao(GLuint value);
	
	// properties
	int width, height, id;
	float tx, ty, scrolRateX, scrolRateY;
	GLuint tid, vao;
};
