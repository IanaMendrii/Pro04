#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "Section.h"

using namespace std;

class Parsing
{

public:
    bool is_Section(string &str);
    bool is_SectionParam(string &str);
    int GetTypeLine(string &str);
    void PrintVec(vector<Section> &sectionVec);
    void GetLines(string &filename, vector<Section> &sectionVec);
};