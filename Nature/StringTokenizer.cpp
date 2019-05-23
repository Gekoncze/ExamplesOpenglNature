#include "StringTokenizer.h"
#include "IndexOutOfBoundsException.h"
#include "StringUtilities.h"

static bool isDelim(char ch, std::string delimiters);

StringTokenizer::StringTokenizer(std::string text, std::string delimiters)
{
	p = 0;
	int begin = 0;
	int end = 0;
	bool searching = true;
	for (int i = 0; i < text.length(); i++)
	{
		char ch = text[i];
		bool d = isDelim(ch, delimiters);
		if (searching)
		{
			if (!d)
			{
				searching = false;
				begin = i;
			}
		}
		else
		{
			if (d)
			{
				searching = true;
				end = i;
				tokens.push_back(text.substr(begin, end - begin));
			}
		}
	}

	if (!searching)
	{
		end = text.length();
		tokens.push_back(text.substr(begin, end - begin));
	}
}

StringTokenizer::~StringTokenizer()
{
}

bool StringTokenizer::hasMoreTokens()
{
	return p >= 0 && p < tokens.size();
}

std::string StringTokenizer::nextToken()
{
	if (p < 0 || p >= tokens.size()) throw IndexOutOfBoundsException(std::string("String tokenizer index out of bounds: ") + p + " out of " + tokens.size());
	return tokens[p++];
}

static bool isDelim(char ch, std::string delimiters)
{
	for (int i = 0; i < delimiters.length(); i++) if (ch == delimiters[i]) return true;
	return false;
}
