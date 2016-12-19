#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
class Window
{
public:
	Window();

	void create(std::string name, GLint width, GLint height);
	void setTitle(std::string name);
	void changeSize(GLint width, GLint height);

	GLint getWidth() { return width; }
	GLint getHeight() { return height; }

	void swapBuffer();

	~Window();

private:

	SDL_Window* window;
	GLint width, height;

};

