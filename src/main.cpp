#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Err_Config.h"
#include "Err_File.h"
#include "Parsing.h"
#include "ReadWrite.h"
#include "Section.h"
using namespace std;

int main(int argc, char *argv[])
{

    ReadWrite RW;
    Parsing parsing;
    enum mode modeType;
    int pos[10];
    std::fill(pos, pos + 10, 0);
    int n; //number of arguments
    string filename = "";
    vector<Section> sectionVec;
    try
    {
		if (argc == 1)
    {
        throw Err_File("File path not specified");
    }
	    RW.Ishelp(argc, argv);
        modeType = RW.ReadArg(argc, argv, pos, n);
        switch (modeType)
        {
        case Default: //default mode;
            filename = argv[1];
            parsing.GetLines(filename, sectionVec);
            parsing.PrintVec(sectionVec);
            break;
        case ReadMode: // read mode;
        {
            vector<string> keyforRead;
            RW.GetKeyForRead(argv, pos, n, keyforRead, filename);

            if (RW.CheckIskeyCorrect(keyforRead))
                parsing.GetLines(filename, sectionVec);
            RW.SearchForKeys(keyforRead, sectionVec);
            break;
        }
        case WriteMode: //write mode;
        {
            vector<dataForWriting> vecdataForWriting;
            RW.GetDataForWriting(argv, pos, n, vecdataForWriting, filename);
            if (RW.CheckIsdataCorrect(vecdataForWriting))
                parsing.GetLines(filename, sectionVec);
            RW.WritingData(vecdataForWriting, sectionVec, filename);
            break;
        }
        }
    }
    catch (Err_File &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "]!\n"
             << err.usage_Param() << endl;
    }
    //system("pause");
    return 0;
}
