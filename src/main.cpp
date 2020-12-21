#include <iostream>
#include <string>
#include <fstream>
#include "Err_Config.h"
#include "Err_File.h"
#include "Parsing.h"
using namespace std;
int main(int argc, char *argv[])
{
    Parsing parsing;
    try
    {
        parsing.GetLines(argc, argv);
    }
    catch (Err_File &err)
    {
        cout << endl;
        cout << err.get_type() << "[" << err.message << "]!\n"
             << err.usage_type() << endl;
    }

    system("pause");
    return 0;
}

