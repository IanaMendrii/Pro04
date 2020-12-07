#pragma once
#include <iostream>
#include <string>
using namespace std;
class Err_Config
{
public:
	string message;
	Err_Config(string message) : message(message) {}
	string get_type()
	{
		return "Error: ";
	}
};