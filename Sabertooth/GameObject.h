#include <GL\glew.h>
class GameObject
{
public:
	GameObject();
	void nextFrame();
	void setVao(GLuint value);
	void setId(int value);
	void setTid(GLuint value);
	int vao, currentFram, id, tid;
};