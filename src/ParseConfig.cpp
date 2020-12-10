#include "ParseConfig.h"
#include "Config.h"
#include "Err_Config.h"
#include "Err_File.h"
#include <fstream>
using namespace std;
Config config;
void ParseConfig::IsAnyEmptySection()
{
	vector <string> SectionConf;

	int size = Section.size();
	int sizeConfig = ConfigLine.size();
	for (int it = 0; it < sizeConfig - 1; it++)
		SectionConf.push_back(ConfigLine[it].GetSection());

	for (int it = 0; it < size - 1; it++)
	{
		if (count(SectionConf.begin(), SectionConf.end(), Section[it]) == 0)
			cerr << "Warning: " << "[Section " + Section[it] + " is empty]!\n";
	}
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
	int(*IsSpace)(int) = isspace;
	if (find_if_not(a.begin(), a.end(), IsSpace) != a.end())
	{
		throw Err_Config(" unexpected symbol/s before [ ");
	}
		a = str.substr(n2 + 2);

		if (find_if_not(a.begin(), a.end(), IsSpace) != a.end())
		{
			throw Err_Config(" unexpected symbol/s after ] ");
		}
		return str.substr(n1, n2);
	}
void ParseConfig::addSection(string& str)
	{
	    CurSection =ExtractSection(str);
		config.IsAnySymbol(CurSection);
		config.removeSpaces(CurSection);
		config.CheckFirstSymbol(CurSection);
		config.CheckSymbol(CurSection);
		config.IsUnique(CurSection, Section);
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
		config.IsAnySymbol(key);
		config.IsAnySymbol(value);
		config.removeSpaces(key);
		config.removeSpaces(value);
		config.isInsideSpace(key);
		config.isInsideSpace(value);
		config.CheckFirstSymbol(key);
		config.CheckSymbol(key);
		config.IsUnique(key, CurSection, ConfigLine);
		ConfigLine.push_back(Config(CurSection, key, value));


	}
void ParseConfig::parseLine(string& str)
	{
		if (str.empty())
			return;
		else if (is_Section(str))
		{
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
void  ParseConfig::Start(int argc, char *argv[])
{
	if (argc == 1)
	{
		throw Err_File("File path not specified");
	}

	fstream file(argv[1], ios::in);
	if (!file.is_open())
	{
		throw Err_File("File not is found");
	}
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		file.seekg(0, std::ios::beg);
		if (size == 0)
			throw Err_File("File  is empty");
	
		
		
			
	string str;
	int numLine = 0;
	vector<string> strLine;
			while (getline(file, str))
		{
			strLine.push_back("Line" + to_string(numLine) + ": " + str);
			{
				try
			{
			parseLine(str);
			}
				catch (Err_Config& err)
				{
					cout << endl;
					cout << err.get_type() << "[" << err.message << "]! in " <<strLine[numLine]<< endl;
					exit(1);
				}
			}
		numLine++;
		}
	IsAnyEmptySection();
	file.close();

}