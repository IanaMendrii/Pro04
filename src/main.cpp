#include <iostream>
#include <string>
#include <fstream>
#include "ParseConfig.h"
#include "Err_Config.h"
#include "Config.h"
#include "Sections.h"
#include "KeyValuePair.h"
using namespace std;

int main(int argc, char *argv[])
{


	fstream file(argv[1], ios::in);

	if (!file.is_open())
	{
		cerr << "File not is found" << endl;
		exit(1);
	}
	ParseConfig ParseConfig;
	string str;
	int numLine = 0;
	vector<string> strLine;
	while (getline(file, str))
	{


		strLine.push_back("Line" + to_string(numLine) + ": " + str);
		{
			try
			{
				ParseConfig.parseLine(str);
			}
			catch (Err_Config& err)
			{
				cout << endl;
				cout << err.get_type() << "[" << err.message << "]! in " << strLine[numLine] << endl;
				exit(1);
			}
		}
		numLine++;
	}
	if (numLine == 0)
	{
		cerr << "File is empty" << endl;
		exit(1);

	}
	system("pause");
	return 0;
}



