#include "File.h"

#include <iostream>
#include <fstream>
#include <string>


std::string File::readFile(const char* path)
{
	std::string line;
	std::ifstream file(path);

	std::string out = "";

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			out += line + "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Failed to open file: " << path << std::endl;
	}

	return out;
}
