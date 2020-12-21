#pragma once
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Parsing
{

public:
    int GetTypeLine(string &str);
    void GetLines(int argc, char *argv[]);
};