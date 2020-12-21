#include "Parsing.h"
#include "Err_File.h"
#include "Err_Config.h"
#include "Section.h"
#include "SectionParam.h"
#include <fstream>
#include "Configfile.h"
Configfile configfile;

int Parsing::GetTypeLine(string &str)
{
    if (str.empty())
        return -1;
    else if (configfile.is_Section(str))
        return 1;
    else if (configfile.is_SectionParam(str))
        return 0;
    else
        throw Err_Config("Line is not valid");
}
void Parsing::GetLines(int argc, char *argv[])
{
    if (argc == 1)
    {
        throw Err_File("File path not specified");
    }

    fstream file(argv[1], ios::in);
    if (!file.is_open())
    {
        throw Err_File("File not is found");
    }
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    if (size == 0)
        throw Err_File("File  is empty");
    string str;
    int LineType = 999;
    string CurSection = "";
    int numLine = 0;
    vector<string> Pair;
    vector<Section> *section = new vector<Section>;
    vector<string> strLine;
    try
    {

        while (getline(file, str))
        {
            numLine++;
            strLine.push_back(str);
            LineType = GetTypeLine(str);
            switch (LineType)
            {
            case 1: //Section;
                if (CurSection != "")
                {
                    configfile.addSection(Pair, CurSection, *section, numLine);
                }
                CurSection = configfile.ExtractSection(str, numLine);
                break;
            case 0: //SectionParam;
                if (CurSection == "")
                    throw Err_Config("Line does not occur within a section");
                Pair.push_back(str);
                break;
            case -1:
                continue;
            }
        }
        configfile.addSection(Pair, CurSection, *section, numLine);
        configfile.PrintVec(*section);
        file.close();
    }

    catch (Err_Config &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "]! in Line " << numLine << " [" << strLine[numLine] << "]" << endl;
        exit(1);
    }
}