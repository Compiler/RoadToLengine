#include "IOManager.h"
#include <fstream>
#include <iostream>

IOManager::IOManager()
{
}












void IOManager::read(const char *filePath, std::string &info) {

	std::fstream file;
	file.open(filePath);

	if (file.fail()) {
		std::cout << "Couldn't open: \"" << filePath << "\"\n";
		return;
	}

	std::vector<GLchar> vec;
	if (!file.eof() && !file.fail())
	{
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();


		vec.resize(fileSize);

		file.seekg(0, std::ios_base::beg);
		file.read(&vec[0], fileSize);
		info = "";
		for(int i = 0; i < vec.size(); i++)
			info += vec[i];

	}
}



/*
	Users responsablility to allocate enough memory
*/
void IOManager::read(const char *filePath, char *info) {

	std::fstream file;
	file.open(filePath);

	if (file.fail()) {
		std::cout << "Couldn't open: \"" << filePath << "\"\n";
		return;
	}
	

	if (!file.eof() && !file.fail())
	{
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();
		

		file.seekg(0, std::ios_base::beg);
		file.read(info, fileSize);
		info[fileSize] = '\0';
	}

}



void IOManager::read(const char *filePath, std::vector<GLchar> &vec) {
	std::fstream file;
	file.open(filePath);

	if (file.fail()) {
		std::cout << "Couldn't open: \"" << filePath << "\"\n";
		return;
	}



	if (!file.eof() && !file.fail())
	{
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();
		vec.resize(fileSize);

		file.seekg(0, std::ios_base::beg);
		file.read(&vec[0], fileSize);
	}

}
IOManager::~IOManager()
{
}