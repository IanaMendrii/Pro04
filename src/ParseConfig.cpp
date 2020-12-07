#include "ParseConfig.h"
#include "Config.h"
#include "Sections.h"
#include "KeyValuePair.h"
#include "Err_Config.h"
using namespace std;
Config *sConfig = new Sections();
Config *kConfig = new KeyValuePair();

void ParseConfig::IsEmptySection()
	{
		if (Section.size() == 0) return;
		string a = "";
		if (ConfigLine.size()>0)
			a = ConfigLine[ConfigLine.size() - 1].GetSection();
		if (Section[Section.size() - 1] != a || ConfigLine.size() == 0)
			cerr << "Warning: " << "[Section " + Section[Section.size() - 1] + " is empty]!\n";
	}

bool ParseConfig::is_Section(string &str)
	{ 
		return count(str.begin(), str.end(), '[') == 1 && count(str.begin(), str.end(), ']') == 1;
	}
string ParseConfig::ExtractSection(string &str)
	{
		int n1, n2;
		size_t found = str.find("[");
		if (found != string::npos)
			n1 = found + 1;
		found = str.find("]");
		if (found != string::npos)
			n2 = found - n1;
		string a = str.substr(0, n1 - 1);
		if (a.find_first_not_of(' ') != string::npos) 
			throw Err_Config(" unexpected symbol/s before [ ");
		a = str.substr(n2 + 2);
		if (a.find_first_not_of(' ') != string::npos) 
			throw Err_Config(" unexpected symbol/s after ] ");
		return str.substr(n1, n2);
	}
void ParseConfig::addSection(string& str)
	{
	    CurSection =ExtractSection(str);
		sConfig->IsAnySymbol(CurSection);
		sConfig->removeSpaces(CurSection);
		sConfig->CheckFirstSymbol(CurSection);
		sConfig->CheckSymbol(CurSection);
		sConfig->IsUnique(CurSection, Section);
		Section.push_back(CurSection);
	}
bool ParseConfig::is_KeyValuePair(string &str)
	{
		return count(str.begin(), str.end(), '=') == 1;
	}
void ParseConfig::SplitKeyValuePair(string &str, string &key, string &value)
	{
		stringstream stream(str);
		string word;
		int i = 0;
		while (getline(stream, word, '='))
		{
			if (i == 0) key = word;
			if (i == 1) value = word;
			i++;
		}

	}
void ParseConfig::addKeyValuePair(string& str)
	{
		if (Section.empty())
		{
			throw Err_Config("Line does not occur within a section");
		}

		string key, value;
		SplitKeyValuePair(str, key, value);
		kConfig->IsAnySymbol(key);
		kConfig->IsAnySymbol(value);
		kConfig->removeSpaces(key);
		kConfig->removeSpaces(value);
		kConfig->isInsideSpace(key);
		kConfig->isInsideSpace(value);
		kConfig->CheckFirstSymbol(key);
		kConfig->CheckSymbol(key);
		kConfig->IsUnique(key, CurSection, ConfigLine);
		ConfigLine.push_back(Config(CurSection, key, value));


	}
void ParseConfig::parseLine(string& str)
	{


		if (str.empty())
			return;
		else if (is_Section(str))
		{
			IsEmptySection();
			addSection(str);
		}
		else if (is_KeyValuePair(str))
		{
			addKeyValuePair(str);
			ConfigLine[ConfigLine.size() - 1].ShowLine();
		}
		else
			throw Err_Config("Line is not valid");


	}
