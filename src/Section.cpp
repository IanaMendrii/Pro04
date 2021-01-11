#include "Section.h"
#include "SectionParam.h"
#include "Err_Config.h"
SectionParam sectionParam;
void Section::removeSpaces(string &line)
{
    sectionParam.removeSpaces(line);
}
void Section::CheckFirstSymbol(string &Line)
{
    sectionParam.CheckFirstSymbol(Line);
}
void Section::CheckSymbol(string &Line)
{
    sectionParam.CheckSymbol(Line);
}
bool Section::IsSectionUnique(string &CurSection, vector<Section> &sectionVec)
{
    for (unsigned i = 0; i < sectionVec.size(); i++)
        if (sectionVec[i].GetSectionName() == CurSection)
            return false;
    return true;
}
string Section::ExtractSection(string &str, int NumLine)
{
    int n1, n2;
    size_t found = str.find("[");
    if (found != string::npos)
        n1 = found + 1;
    found = str.find("]");
    if (found != string::npos)
        n2 = found - n1;
    string SectionName = str.substr(n1, n2);
    int (*IsSpace)(int) = isspace;
    try
    {
        string a = str.substr(0, n1 - 1);
        if (!all_of(a.begin(), a.end(), IsSpace))
        {
            throw Err_Config(" unexpected symbol/s before '[' ");
        }
        a = str.substr(n1 + n2 + 1);
        if (!all_of(a.begin(), a.end(), IsSpace))
        {
            throw Err_Config(" unexpected symbol/s after ']' ");
        }
        if (SectionName.empty() || all_of(SectionName.begin(), SectionName.end(), IsSpace))
            throw Err_Config("There is no symbol for section definition");
        removeSpaces(SectionName);
        CheckFirstSymbol(SectionName);
        CheckSymbol(SectionName);
    }
    catch (Err_Config &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "]! in Line " << NumLine << "[" << str << "]\n";
        cout << err.usage_typeSection() << endl;
        exit(1);
    }
    return SectionName;
}
void Section::addSection(vector<string> &Pair, string &CurSection, vector<Section> &sectionVec, int &NumLine)
{
    if (Pair.empty())
        cerr << "Warning: "
             << "[Section " + CurSection + " is empty]!\n";
    sectionParam.addParam(Pair, Param, NumLine);
    sectionVec.push_back(Section(CurSection, Param));
}
