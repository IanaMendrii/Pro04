#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
class SectionParam
{
private:
    string m_key;
    string m_value;

public:
    SectionParam(string &key, string &value)
        : m_key(key), m_value(value)
    {
    }
    SectionParam()
    {
    }
    string GetKey() const
    {
        return m_key;
    }
    string GetValue() const
    {
        return m_value;
    }

    void removeSpaces(string &line);
    void CheckFirstSymbol(string &Line);
    void CheckSymbol(string &Line);
    void isInsideSpace(string &Line);
    bool IsKeyUnique(string &key, vector<SectionParam> &Param);
    void SplitParam(string &str, string &key, string &value);
	void addParam(vector<string> &Pair, vector<SectionParam> &Param, int numLine);
};