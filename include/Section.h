#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "SectionParam.h"
#include <sstream>

using namespace std;
class Section
{
private:
    string m_SectionName;
    vector<SectionParam> Param;

public:
    string GetSectionName() const
    {
        return m_SectionName;
    }
    vector<SectionParam> &GetParam()
    {
        return Param;
    }
    Section(string SectionName, vector<SectionParam> Param) : m_SectionName(SectionName), Param(Param.begin(), Param.end())
    {
    }
    Section()
    {
    }
    void removeSpaces(string &line);
    void CheckFirstSymbol(string &Line);
    void CheckSymbol(string &Line);
    bool IsSectionUnique(string &CurSection, vector<Section> &section);
    void addSection(vector<string> &Pair, string &CurSection, vector<Section> &section, int &NumLine);
    string ExtractSection(string &str, int NumLine);
};
