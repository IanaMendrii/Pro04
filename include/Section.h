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
    void addParam(vector<string> &Pair, vector<SectionParam> &Param, int numLine);
    void removeSpaces(string &line);
    void CheckFirstSymbol(string &Line);
    void CheckSymbol(string &Line);
    bool IsSectionUnique(string &CurSection, vector<Section> &section);
};
