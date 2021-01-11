#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "Section.h"

using namespace std;
enum mode { Default, ReadMode, WriteMode };
struct dataForWriting
{
	string section;
	string key;
	string value;
};
class ReadWrite
{

public:
	 void Ishelp(int argc, char *argv[]);
	 enum mode ReadArg(int argc, char *argv[], int pos[], int&n);
	 bool CheckIskeyCorrect(vector<string> &keyforRead);
	 bool CheckIsdataCorrect(vector<dataForWriting> &vecdataForWriting);
	 void GetKeyForRead(char *argv[], int *posR, int nr, vector<string> &keyforRead, string &filename);
	 void GetDataForWriting(char *argv[], int *posW, int nw, vector<dataForWriting> &vecdataForWriting, string &filename);
	 void SearchForKeys(vector<string> &keyforRead, vector<Section> &sectionVec);
	 bool SearchForOneKey(string &key, vector<Section> &sectionVec);
	 void WritingData(vector<dataForWriting> &vecdataForWriting, vector<Section> &sectionVec, string &filename);
};