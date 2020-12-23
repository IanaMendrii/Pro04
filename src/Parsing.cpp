#include "Parsing.h"
#include "Err_File.h"
#include "Err_Config.h"
#include "Section.h"
#include "SectionParam.h"
#include <fstream>
Section section;
bool Parsing::is_Section(string &str)
{
	return count(str.begin(), str.end(), '[') == 1 && count(str.begin(), str.end(), ']') == 1;
}
bool Parsing::is_SectionParam(string &str)
{
	return count(str.begin(), str.end(), '=') == 1;
}
int Parsing::GetTypeLine(string &str)
{
    if (str.empty())
        return -1;
	else if (is_Section(str))
        return 1;
	else if (is_SectionParam(str))
		return 0;
	else
		return -2;
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
    vector<Section> sectionVec;
    try
    {

        while (getline(file, str))
        {
            numLine++;
            LineType = GetTypeLine(str);
            switch (LineType)
            {
            case 1: //Section;
                if (CurSection != "")
                {
					
					section.addSection(Pair, CurSection, sectionVec, numLine);
                }
                CurSection = section.ExtractSection(str, numLine);
				if (!section.IsSectionUnique(CurSection, sectionVec))
				{
					throw Err_Config("Section " + CurSection + " appears twice in Config file");
				}
                break;
            case 0: //SectionParam;
                if (CurSection == "")
                    throw Err_Config("Line does not occur within a section");
                Pair.push_back(str);
                break;
            case -1:
                break;
			case -2:
				throw Err_Config("Line is not valid");
				break;
            }
        }
        section.addSection(Pair, CurSection, sectionVec, numLine);
        section.PrintVec(sectionVec);
        file.close();
    }

    catch (Err_Config &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "]! in Line " << numLine << " [" << str << "]" << endl;
        exit(1);
    }
}