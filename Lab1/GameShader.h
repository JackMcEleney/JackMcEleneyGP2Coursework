#pragma once
#include <string>
#include <GL\glew.h>
#include "Position.h"
#include "Cam.h"

class GameShader
{
public:
	GameShader(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Position& position, const Cam& cam);

	std::string GameShader::LoadShader(const std::string& fileName);
	void GameShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint GameShader::CreateShader(const std::string& text, unsigned int type);

    ~GameShader();


protected:
private:
	static const unsigned int NumOfShaders = 2; // number of shaders

	enum
	{
		UniformTransform,

		NumOfUniforms
	};

	GLuint program; // Track the shader program
	GLuint shaders[NumOfShaders]; //array of shaders
	GLuint uniforms[NumOfUniforms]; //no of uniform variables
};
