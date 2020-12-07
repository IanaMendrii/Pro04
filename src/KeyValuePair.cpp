#include "Config.h"
#include "KeyValuePair.h"
#include "Err_Config.h"
using namespace std;
void KeyValuePair::IsUnique(string &key, string &CurSection, vector <Config> &ConfigLine)
	{
		int size = ConfigLine.size();
		if (size == 0) return;
		int it = size - 1;
		while (it >= 0 && CurSection == ConfigLine[it].GetSection())
		{

			if (key == ConfigLine[it].GetKey())
				throw Err_Config("Key " + key + " appears twice in Section");
			--it;
		}
	}
