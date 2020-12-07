#pragma once
#include "Config.h"
using namespace std;
class Sections :public Config
{
	virtual void IsUnique(string& CurSection, vector <string> &Section)override;
};