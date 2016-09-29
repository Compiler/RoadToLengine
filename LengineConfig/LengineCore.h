#pragma once

#include <SDL\SDL.h>


class LengineCore{
public:
	LengineCore();


	void run();
	void setHeight();
	void setWidth();
	void setFlag();
	~LengineCore();

private:

	void initSubSystems();
	void render();
	void update();


	unsigned int width, height;
	SDL_Window* window;
	SDL_Event event;

};
