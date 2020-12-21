#include "Configfile.h"
#include "SectionParam.h"
#include "Section.h"
#include "Err_Config.h"
Section sectionName;
vector<SectionParam> *Param = new vector<SectionParam>;
bool Configfile::is_Section(string &str)
{
    return count(str.begin(), str.end(), '[') == 1 && count(str.begin(), str.end(), ']') == 1;
}
bool Configfile::is_SectionParam(string &str)
{
    return count(str.begin(), str.end(), '=') == 1;
}
string Configfile::ExtractSection(string &str, int NumLine)
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
        a = str.substr(n2 +2);
        if (!all_of(a.begin(), a.end(), IsSpace))
        {
            throw Err_Config(" unexpected symbol/s after ']' ");
        }
        if (SectionName.empty() || all_of(SectionName.begin(), SectionName.end(), IsSpace))
            throw Err_Config("There is no symbol for section definition");
        sectionName.removeSpaces(SectionName);
        sectionName.CheckFirstSymbol(SectionName);
        sectionName.CheckSymbol(SectionName);
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
void Configfile::addSection(vector<string> &Pair, string &CurSection, vector<Section> &section, int &NumLine)
{
    if (!sectionName.IsSectionUnique(CurSection, section))
    {
        NumLine = NumLine - Pair.size() - 1;
        throw Err_Config("Section " + CurSection + " appears twice in Config file");
    }
    if (Pair.empty())
        cerr << "Warning: "
             << "[Section " + CurSection + " is empty]!\n";
    sectionName.addParam(Pair, *Param, NumLine);
    section.push_back(Section(CurSection, *Param));
}
void Configfile::PrintVec(vector<Section> &section)
{
    for (auto it = section.begin(); it != section.end(); it++)
    {
        for (auto l = it->GetParam().begin(); l != it->GetParam().end(); l++)
            cout << it->GetSectionName() << "." << l->GetKey() << ":" << l->GetValue() << "\n";
    }
}
