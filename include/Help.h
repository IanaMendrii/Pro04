#pragma once
#include <iostream>
#include <string>
using namespace std;
string help_type()
{
    return "usage: Pro04.exe [<options>] <path to Config file> [<options>]\n"
           "\n"
           "The program is dedicated to parse Gonfig file with the following structure: \n"
           "[SectionName]\n"
           "key_1 = value_1\n"
           "key_2 = value_2\n"
           "...............\n"
           "Section can only include letters, digits, underscore, and space.\n"
           "Key can only include letters, digits, underscore; \n"
           "Value can contain any symbols except space;\n"
           "Name of Section and Key must begin with a letter.\n"
           "Whitespace and empty lines are permitted.\n"
           "Duplication Sections and Keys inside the section are prohibited.\n"
           "\n"
           "-h, --help               Print this help and exit successfully;\n"
           "-r, --read-parameter     Read and print only specified parameters from file\n"
           "                         This option is followed by [key];\n"
           "-w, --write-parameter    Write new parameters in file\n"
           "                         This option is followed by [section] [key] [value];\n"
           "Only one option --read-parameter or --write-parameter can be utilized at once.\n"
           "If [section] contains inside space double quotes are used.\n";
}