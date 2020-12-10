#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
#include <sstream>
using namespace std;
class Config
{
private:
	string m_section;
	string m_key;
	string m_value;
public:
	Config(string &section, string &key, string &value)
		:m_section(section), m_key(key), m_value(value)
	{}
	Config()
	{}
	string GetSection()const
	{
		return m_section;
	}
	string GetKey()const
	{
		return m_key;
	}
	string GetValue()const
	{
		return m_value;
	}
	void ShowLine()
	{
		cout << m_section << '.' << m_key << " : " << m_value << endl;
	}
	void IsAnySymbol(string &line);
	void removeSpaces(string &line);
	void CheckFirstSymbol(string &Line);
	void CheckSymbol(string &Line);
	void isInsideSpace(string &Line);
	void IsUnique(string& CurSection, vector <string> &Section);
	void IsUnique(string &key, string &CurSection, vector <Config> &ConfigLine);
};