#pragma once
#include <string>
#include <vector>

class StringTokenizer
{
private:
	std::vector<std::string> tokens;
	int p;

public:
	StringTokenizer(std::string text, std::string delimiters);
	~StringTokenizer();
	bool hasMoreTokens();
	std::string nextToken();
};

