#include <iostream>
#include <string>
#include <fstream>
#include "ParseConfig.h"
#include "Err_Config.h"
#include "Err_File.h"
#include "Config.h"
using namespace std;
int main(int argc, char *argv[])
{
	ParseConfig ParseConfig;
	try
	{
		ParseConfig.Start(argc, argv);
	}
	catch (Err_File& err)
	{
		cout << endl;
		cout << err.get_type() << "[" << err.message << "]!\n" << err.usage_type() << endl;
	}
	
	return 0;
}



