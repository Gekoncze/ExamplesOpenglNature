#include "FileReader.h"
#include "Logger.h"
#include "IOException.h"

FileReader::FileReader(std::string path)
{
	stream.open(path);
	if (!stream || stream.fail()) throw IOException("Could not open " + path);
}

FileReader::~FileReader()
{
	stream.close();
}

bool FileReader::readLine(std::string& line)
{
	if (std::getline(stream, line)) return true;
	else return false;
}

std::string FileReader::readAll(std::string path)
{
	FileReader reader(path);
	std::string content;
	std::string line;
	while (reader.readLine(line)) content.append(line).append("\n");
	return content;
}
