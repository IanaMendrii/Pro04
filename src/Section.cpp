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
bool Section::IsSectionUnique(string &CurSection, vector<Section> &section)
{
    for (unsigned i = 0; i < section.size(); i++)
        if (section[i].GetSectionName() == CurSection)
            return false;
    return true;
}
void Section::addParam(vector<string> &Pair, vector<SectionParam> &Param, int numLine)
{
    string key, value;
    Param.clear();

    for (unsigned int it = 0; it < Pair.size(); it++)
    {
        try
        {
            sectionParam.SplitParam(Pair[it], key, value);
            if (!sectionParam.IsKeyUnique(key, Param))
                throw Err_Config("Key " + key + " appears twice in Section");
            Param.push_back(SectionParam(key, value));
        }
        catch (Err_Config &err)
        {
            cout << endl;
            cout << err.get_type() << "[" << err.message << "]! in Line " << numLine + it << " [" << Pair[it] << "]" << endl;
            cout << err.usage_typeParam() << endl;
            exit(1);
        }
    }

    Pair.clear();
}