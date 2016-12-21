#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Error.h"
#include "Window.h"
#include "GameState.h"
#include "InputListener.h"
#include "ShaderProgram.h"
class Core
{
public:
	Core();

	void run();

	~Core();
private:

	void inline init();
	void render();
	void update();
	
	void checkSupport();
	GLint width, height;
	GameState currentState;
	InputListener listener;

	ShaderProgram prog;
	Window window;


	GLuint arrayID, bufferID;
	

};

