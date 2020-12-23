#pragma once
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Parsing
{

public:
	bool is_Section(string &str);
	bool is_SectionParam(string &str);
    int GetTypeLine(string &str);
	void GetLines(int argc, char *argv[]);
};