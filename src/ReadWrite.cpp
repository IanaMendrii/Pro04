#include "ReadWrite.h"
#include "SectionParam.h"
#include "Section.h"
#include <vector>
#include "Err_File.h"
#include "Err_Config.h"
#include "Help.h"
#include <fstream>
SectionParam SP;
void ReadWrite::Ishelp(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h")
        {
            cout << help_type() << endl;
            exit(0);
        }
    }
}
enum mode ReadWrite::ReadArg(int argc, char *argv[], int pos[], int &n)
{
    int nr = 0;
    int nw = 0;
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]).substr(0, 1) != "-")
            continue;
        if (std::string(argv[i]) == "--read-parameter" || std::string(argv[i]) == "-r")
        {
            if (nw != 0)
            {
                cout << "Only one option --read - parameter or --write - parameter can be utilized at once.\n";
                exit(1);
            }
            else
            {

                pos[nr] = i;
                nr++;
            }
        }
        else if (std::string(argv[i]) == "--write-parameter" || std::string(argv[i]) == "-w")
        {
            if (nr != 0)
            {
                cout << "Only one option --read-parameter or --write-parameter can be utilized at once.\n";
                exit(1);
            }
            else
            {
                pos[nw] = i;
                nw++;
            }
        }
        else
        {
            throw Err_File("Unknown option " + std::string(argv[i]));
        }
    }
    if (nr != 0 && nw == 0)
    {
        pos[nr] = argc;
        n = nr;
        return ReadMode;
    }
    if (nr == 0 && nw != 0)
    {
        pos[nw] = argc;
        n = nw;
        return WriteMode;
    }
    return Default;
}
bool ReadWrite::CheckIskeyCorrect(vector<string> &keyforRead)
{
    string line;
    try
    {
        for (unsigned i = 0; i < keyforRead.size(); i++)
        {
            line = keyforRead[i];
            SP.CheckFirstSymbol(line);
            SP.CheckSymbol(line);
            SP.isInsideSpace(line);
        }
    }
    catch (Err_Config &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "] " << line << "\n";
        cout << err.usage_typeParamRW() << endl;
        exit(1);
    }
    return true;
}
bool ReadWrite::CheckIsdataCorrect(vector<dataForWriting> &vecdataForWriting)
{
    string line;
    for (unsigned i = 0; i < vecdataForWriting.size(); i++)
    {
        try
        {
            line = vecdataForWriting[i].section;
            SP.CheckFirstSymbol(line);
            SP.CheckSymbol(line);
        }
        catch (Err_Config &err)
        {
            cout << endl;
            cout << err.get_type() << "[" << err.message << "] " << line << "\n";
            cout << err.usage_typeSectionRW() << endl;
            exit(1);
        }
        try
        {
            line = vecdataForWriting[i].key;
            SP.CheckFirstSymbol(line);
            SP.CheckSymbol(line);
            SP.isInsideSpace(line);
        }
        catch (Err_Config &err)
        {
            cout << endl;
            cout << err.get_type() << "[" << err.message << "] " << line << "\n";
            cout << err.usage_typeParamRW() << endl;
            exit(1);
        }
    }
    return true;
}

void ReadWrite::GetKeyForRead(char *argv[], int *posR, int nr, vector<string> &keyforRead, string &filename)
{
    for (int i = 1; i <= nr; i++)
    {
        if (posR[i] - posR[i - 1] < 2)
            throw Err_File("Incorrect parameter list:There is no agrument after[--read-parameter]");
        if (posR[i] - posR[i - 1] >= 4)
            throw Err_File("Incorrect parameter list:There are too many agruments after[--read-parameter]");
        else
        {

            keyforRead.push_back(std::string(argv[posR[i - 1] + 1]));
        }
    }
    if (posR[0] != 1)
        filename = argv[1];

    for (int i = 1; i <= nr; i++)
    {
        if (posR[i] - posR[i - 1] == 3)
        {
            if (filename != "")
                throw Err_File("Incorrect parameter list:There are too many agruments after[--read-parameter]");
            filename = argv[posR[i - 1] + 2];
            break;
        }
    }
}
void ReadWrite::GetDataForWriting(char *argv[], int *posW, int nw, vector<dataForWriting> &vecdataForWriting, string &filename)
{
    for (int i = 1; i <= nw; i++)
    {
        if (posW[i] - posW[i - 1] < 4)
            throw Err_File("Incorrect parameter list:There is less than three agrument after[--write-parameter]");
        if (posW[i] - posW[i - 1] >= 6)
            throw Err_File("Incorrect parameter list:There are too many agruments after[--write-parameter]");
        if (posW[i] - posW[i - 1] >= 4)
        {
            vecdataForWriting.push_back(dataForWriting());
            vecdataForWriting[i - 1].section = argv[posW[i - 1] + 1];
            vecdataForWriting[i - 1].key = argv[posW[i - 1] + 2];
            vecdataForWriting[i - 1].value = argv[posW[i - 1] + 3];
        }
    }
    if (posW[0] != 1)
        filename = argv[1];
    for (int i = 1; i <= nw; i++)
    {
        if (posW[i] - posW[i - 1] == 5)
        {
            if (filename != "")
                throw Err_File("Incorrect parameter list:There are too many agruments after[--read-parameter]");
            filename = argv[posW[i - 1] + 4];
            break;
        }
    }
}
bool ReadWrite::SearchForOneKey(string &key, vector<Section> &sectionVec)
{
    bool is = false;
    for (auto it1 = sectionVec.begin(); it1 != sectionVec.end(); it1++)
    {
        for (auto it2 = it1->GetParam().begin(); it2 != it1->GetParam().end(); it2++)
        {
            if (key == it2->GetKey())
            {
                cout << it1->GetSectionName() << "." << it2->GetKey() << ":" << it2->GetValue() << "\n";
                is = true;
            }
        }
    }
    return is;
}
void ReadWrite::SearchForKeys(vector<string> &keyforRead, vector<Section> &sectionVec)
{
    string key;
    for (auto it = keyforRead.begin(); it != keyforRead.end(); it++)
    {
        key = *it;
        if (!SearchForOneKey(key, sectionVec))
            std::cout << "Key [" << key << "] is not found" << endl;
    }
}
void WriteToFile(vector<Section> &sectionVec, string &filename)
{
    fstream file(filename, ios::out);
    for (auto it = sectionVec.begin(); it != sectionVec.end(); it++)
    {
        file << "[" << it->GetSectionName() << "]\n";
        for (auto l = it->GetParam().begin(); l != it->GetParam().end(); l++)
            file << l->GetKey() << "=" << l->GetValue() << "\n";
    }
}
bool ReadWrite::IsKeyExist(string &key, string &value, vector<SectionParam> &Param)
{
    for (unsigned i = 0; i < Param.size(); i++)
        if (Param[i].GetKey() == key)
        {
            Param[i].SetValue(value);
            return false;
        }
    return true;
}
void ReadWrite::WritingData(vector<dataForWriting> &vecdataForWriting, vector<Section> &sectionVec, string &filename)
{
    string section;
    bool is = false;
    vector<SectionParam> Param;
    for (auto it = vecdataForWriting.begin(); it != vecdataForWriting.end(); it++)
    {
        is = false;
        section = it->section;
        for (auto it1 = sectionVec.begin(); it1 != sectionVec.end(); it1++)
        {
            if (section == it1->GetSectionName())
            {
                if (!IsKeyExist(it->key, it->value, it1->GetParam()))
                {
                    std::cout << "The object: " << it->section << "." << it->key << ":" << it->value << " has been successfully rewrited in config file\n";
                    is = true;
                }
                else
                {
                    it1->GetParam().push_back(SectionParam(it->key, it->value));
                    std::cout << "The object: " << it->section << "." << it->key << ":" << it->value << " has been successfully added in config file\n";
                    is = true;
                }
            }
        }
        if (!is)
        {

            Param.push_back(SectionParam(it->key, it->value));
            sectionVec.push_back(Section(section, Param));
            Param.clear();
            std::cout << "The object: " << it->section << "." << it->key << ":" << it->value << " has been successfully added in config file\n";
            std::cout << "Section: " << it->section << " has been created\n";
        }
    }
    WriteToFile(sectionVec, filename);
}