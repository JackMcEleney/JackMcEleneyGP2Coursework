#include "Game.h"
#include "Cam.h"
#include <iostream>
#include <string>



//Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
				//	Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
				//	Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

//unsigned int indices[] = { 0, 1, 2 };

Position position;

Game::Game()
{
	_gameState = GameState::PLAY;
	Window* _gameWindow = new Window(); //new Window
    Meshes* meshes1(); //creates a pointer from Meshes to a new mesh constructor
	Meshes* meshes2();
	Meshes* meshes3();
	Sound* audioDevice();
}

Game::~Game()
{
}

void Game::run()
{
	initializeSystems(); //starts all things needed on start up
	gameLoop(); //starts game loop
}

void Game::initializeSystems()
{
	_gameWindow.initializeWindow(); //creates window settings

	meshes1.loadModel("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\wc1.obj"); //loads a model to corresponding mesh class
	meshes2.loadModel("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\cone.obj");
	meshes3.loadModel("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\pokemon.obj");
	myCam.initializeCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameWindow.getWidth()/_gameWindow.getHeight(), 0.01f, 1000.0f); //camera settings
	counter = 0.0f;
}

void Game::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput(); //allows player to quit
		drawGame(); //draws objects to screen
		collision(meshes1.getSpherePos(), meshes1.getSphereRadius(), meshes2.getSpherePos(), meshes2.getSphereRadius());
	}
}

void Game::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT; //quits the game
				break;
		}
	}
	
}

bool Game::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}


void Game::drawGame()
{
	_gameWindow.clearWindow(0.0f, 0.0f, 0.0f, 1.0f); //clears anything on game window
	
	GameShader shader(".\\res\\shader"); //new shader
	Textures texture("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\wc1_diffuse.tga"); //load texture
	Textures texture1("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\conetexture.png"); //load texture
	Textures texture2("C:\\Users\\Jack\\Desktop\\JackMcEleneyCoursework\\res\\final_pokemon_diffuse.jpg");
	
	position.SetPos(glm::vec3(sinf(counter), 0.0, 0.0)); //sets objects position, changes due to counter
	position.SetRot(glm::vec3(0.0, 0.0, counter * 5)); //sets objects rotation, same as above
	position.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter))); //sets objects scale, same as above

	shader.Bind(); //binds the shader
	shader.Update(position, myCam); //applies shader to scene, objects become visible
	texture.Bind(0); //binds the texture loaded to "texture" to the buffer
	meshes1.draw(); //draws "meshes1" and applies the texture above
	meshes1.updateSphereData(*position.GetPos(), 0.62f);
	//shader.Update(position, myCam);
	texture1.Bind(0); //binds texture1
	meshes2.draw(); //draws and applies texture1
	meshes2.updateSphereData(*position.GetPos(), 0.62f);
	texture2.Bind(0); //binds textire2
	meshes3.draw(); //draws and applies texture2
	counter = counter + 0.01f; //ticks up to cause movement in objects
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd(); //ends drawing of vertices

	_gameWindow.swapBuffer();
} 