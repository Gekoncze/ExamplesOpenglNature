#pragma once

#include <fstream>
#include <string>

class FileReader
{
private:
	std::ifstream stream;

public:
	FileReader(std::string path);
	~FileReader();
	bool readLine(std::string& line);

	static std::string readAll(std::string path);
};

