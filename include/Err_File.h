#pragma once
#include <iostream>
#include <string>
using namespace std;
class Err_File
{
public:
	string message;
	Err_File(string message) : message(message) {}
	string get_type()
	{
		return "Error: ";
	}
	string usage_type()
	{
		return  "usage: Pro04.exe <path to Config file>\n" 
		"\n"
		"The program is dedicated to parse Gonfig file with the following structure : \n"
		 "[SectionName]\n"
		"key_1 = value_1\n"
		"key_2 = value_2\n"
        "...............\n"
		"Section can only include letters, digits, symbol _, and space;\n"
		"Key can only include letters, digits, symbol _; \n"
		"Value can contain any symbols exept space;\n"
		"Name of Section and Key must begin with a letter.\n"
		"Whitespace and empty lines are permitted. \n"
		 "Duplication Sections and Keys inside the section are prohibited. \n";
	}
};