
#include <iostream>
#include <SDL\SDL.h>
#include "LengineCore.h"

//start of app
int main(int argc, char** argv){

	//run the main loop
	LengineCore core;
	core.run();

	//studder for build errors
	char studder;
	std::cin >> studder;
	return 0;
}
