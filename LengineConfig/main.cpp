
#include <iostream>
#include <SDL\SDL.h>
#include "LengineCore.h"
#include <lml\Mat2.h>
#include <GL\glew.h>
//start of app
int main(int argc, char** argv){

	//run the main loop
	LengineCore core;
	core.run();

	return 0;
}
