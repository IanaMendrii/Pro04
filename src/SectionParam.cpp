#include "SectionParam.h"
#include "Err_Config.h"
using namespace std;
void SectionParam::removeSpaces(string &line)
{
    for (unsigned int i = 0; i < line.size(); ++i)
    {
        if (!isspace(line[i]))
        {
            line.erase(0, i);
            break;
        }
    }
    for (unsigned int i = line.size() - 1; i >= 0; --i)
    {
        if (!isspace(line[i]))
        {
            line.erase(i + 1, line.size() - i - 1);
            break;
        }
    }
}
void SectionParam::CheckFirstSymbol(string &Line)
{
    if (!isalpha(Line[0]))
    {
        throw Err_Config("First symbol have to be a Letter");
    }
}

void SectionParam::CheckSymbol(string &Line)
{
    if (all_of(Line.begin(), Line.end(), [](unsigned char c) -> bool { return isalnum(c) || c == '_' || c == ' '; }))
        return;
    else
    {
        auto found = find_if_not(Line.begin(), Line.end(), [](unsigned char c) -> bool { return isalnum(c) || c == '_' || c == ' '; });
        throw Err_Config(*found + " unexpected symbol");
    }
}
void SectionParam::isInsideSpace(string &Line)
{
    if (any_of(Line.begin(), Line.end(), [](unsigned char c) -> bool { return c == ' '; }))
        throw Err_Config("There is unexpected space inside");
}
bool SectionParam::IsKeyUnique(string &key, vector<SectionParam> &Param)
{
    for (unsigned i = 0; i < Param.size(); i++)
        if (Param[i].GetKey() == key)
            return false;
    return true;
}
void SectionParam::SplitParam(string &str, string &key, string &value)
{
    key = "";
    value = "";
    stringstream stream(str);
    string word;
    int i = 0;
    while (getline(stream, word, '='))
    {
        if (i == 0)
            key = word;
        if (i == 1)
            value = word;
        i++;
    }
    int (*IsSpace)(int) = isspace;
    if (key.empty() || all_of(key.begin(), key.end(), IsSpace))
        throw Err_Config("There is no symbol for key definition");
    if (value.empty() || all_of(value.begin(), value.end(), IsSpace))
        throw Err_Config("There is no symbol for value definition");
    removeSpaces(key);
    removeSpaces(value);
    isInsideSpace(key);
    isInsideSpace(value);
    CheckFirstSymbol(key);
    CheckSymbol(key);
}
void SectionParam::addParam(vector<string> &Pair, vector<SectionParam> &Param, int numLine)
{
    string key, value;
    Param.clear();

    for (unsigned int it = 0; it < Pair.size(); it++)
    {
        try
        {
            SplitParam(Pair[it], key, value);
            if (!IsKeyUnique(key, Param))
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
