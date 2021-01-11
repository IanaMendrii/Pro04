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
    string usage_typeSection()
    {
        return "usage:Section can only include letters, digits, underscore, and space. \n"
               "      Name of Section must begin with a letter.\n"
               "      Whitespace and empty lines are permitted.\n"
               "      Duplication Sections are prohibited. \n";
    }
    string usage_typeParam()
    {
        return "usage: Key can only include letters, digits, underscore. \n"
               "       Value can contain any symbols except space;\n"
               "       Key must begin with a letter.\n"
               "       Whitespace and empty lines are permitted.\n"
               "       Duplication Keys inside the section are prohibited. \n";
    }
    string usage_typeSectionRW()
    {
        return "usage:Section can only include letters, digits, underscore, and space. \n"
               "      Name of Section must begin with a letter.\n";
    }
    string usage_typeParamRW()
    {
        return "usage: Key can only include letters, digits, symbol _. \n"
               "       Key must begin with a letter.\n";
    }
};