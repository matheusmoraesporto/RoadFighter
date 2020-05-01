#pragma once
#include <GL\glew.h>
class Layer
{
public:
	Layer();
	Layer(int widthValue, int heightValue, int tidValue);
	//void scroll(glm::mat4& matrix);
	void setTid(GLuint value);
	void setId(int value);
	void setWidth(int value);
	void setHeight(int value);
	void setTx(float value);
	void setTy(float value);
	void setScrollRateX(float value);
	void setScrollRateY(float value);
	void setVao(GLuint value);
	float getTy();
	float getScrollRateY();
	
	// properties
	int width, height, id;
	float tx, ty, scrollRateX, scrollRateY;
	GLuint tid, vao;
};
