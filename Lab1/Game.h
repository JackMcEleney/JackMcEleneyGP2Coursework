#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Window.h" 
#include "GameShader.h"
#include "ObjectMeshes.h"
#include "ObjectTextures.h"
#include "Position.h"
#include "Sound.h"

enum class GameState{PLAY, EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void initializeSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);

	Window _gameWindow;
	GameState _gameState;
	Meshes meshes1;
	Meshes meshes2;
	Meshes meshes3;
	Cam myCam;
	Sound audioDevice;

	float counter;
	unsigned int music;


};

