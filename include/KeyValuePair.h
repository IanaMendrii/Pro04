#pragma once
#include "Config.h"
using namespace std;

class KeyValuePair : public Config
{
	virtual  void IsUnique(string &key, string &CurSection, vector <Config> &ConfigLine)override;
};