#pragma once
#include <string>
#include <GL\glew.h>

class Textures
{
public:
	Textures(const std::string& fileName);

	void Bind(unsigned int unit); // bind upto 32 textures

	~Textures();

protected:
private:

	GLuint handler;
};

