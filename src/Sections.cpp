#include "Config.h"
#include "Sections.h"
#include "Err_Config.h"
using namespace std;
	 void Sections::IsUnique(string& CurSection, vector <string> &Section)
	{
		if (count(Section.begin(), Section.end(), CurSection) != 0)
		{
			throw Err_Config("Section " + CurSection + " appears twice in config file");

		}
	}
