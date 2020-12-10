#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <cassert>
#include <algorithm>
#include "Config.h"
using namespace std;

class ParseConfig
{

public:
	string CurSection;
	vector <string> Section;
	vector <Config> ConfigLine;
	void IsAnyEmptySection();
	void IsEmptySection();
	bool is_Section(string &str);
	string ExtractSection(string &str);
	void addSection(string& str);
	bool is_KeyValuePair(string &str);
	void SplitKeyValuePair(string &str, string &key, string &value);
	void addKeyValuePair(string& str);
	void parseLine(string& str);
	void Start(int argc, char *argv[]);
};