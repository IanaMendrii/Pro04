#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "Section.h"
#include "SectionParam.h"
using namespace std;

class Configfile
{
public:
    vector<Section> section;
    bool is_Section(string &str);
    bool is_SectionParam(string &str);
    void addSection(vector<string> &Pair, string &CurSection, vector<Section> &section, int &NumLine);
    string ExtractSection(string &str, int NumLine);
    void PrintVec(vector<Section> &section);
};