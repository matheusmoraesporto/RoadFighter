#pragma once
#include <GL\glew.h>
class Layer
{
public:
	Layer();
	Layer(int widthValue, int heightValue, int tidValue);
	void setTid(GLuint value);
	void setId(int value);
	void setWidth(int value);
	void setHeight(int value);
	void setTx(float value);
	void setTy(float value);
	void setScrollRateX(float value);
	void setScrollRateY(float value);
	void setVao(GLuint value);
	void setZ(float value);
	void setName(char value);

	char name;
	// properties
	int width, height, id;
	float tx, ty, scrollRateX, scrollRateY, z;
	GLuint tid, vao;
};
