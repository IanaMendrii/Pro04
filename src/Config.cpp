#include "Config.h"
#include "Err_Config.h"
using namespace std;
	void Config::IsAnySymbol(string &line)
	{
		if (line.empty() || all_of(line.begin(), line.end(),
			[](unsigned char c)->bool {	return c == ' '; }))
			throw Err_Config("There is no " + line + " definition");
	}
	void Config::removeSpaces(string &line)
	{
		for (unsigned int i = 0; i <line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				line.erase(0, i); break;
			}
		}
		for (unsigned int i = line.size() - 1; i >= 0; --i)
		{
			if (line[i] != ' ')
			{
				line.erase(i + 1, line.size() - i - 1); break;
			}
		}
	}
	void Config::CheckFirstSymbol(string &Line)
	{
		if (!isalpha(Line[0]))
		{
			throw Err_Config("First symbol have to be a Letter");
		}
	}
	
	void Config::CheckSymbol(string &Line)
	{
		if (all_of(Line.begin(), Line.end(), [](unsigned char c)->bool {
			return isalnum(c) || c == '_' || c == ' '; }))
			    return;
		else
		{
			auto found = find_if_not(Line.begin(), Line.end(), [](unsigned char c)->bool {
				return isalnum(c) || c == '_' || c == ' '; });
				throw Err_Config(*found + " unexpected symbol");

		}
	}
	void Config::isInsideSpace(string &Line)
	{
		if (any_of(Line.begin(), Line.end(), [](unsigned char c)->bool {
			return c == ' '; }))
				throw Err_Config("There is unexpected space inside line");
	}
