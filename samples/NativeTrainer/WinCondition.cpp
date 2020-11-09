#include "WinCondition.h"

void WinCondition(bool& wincontrol, int& wincondition, DWORD& wintimertext, int totalpeds, Ped* missionpeds,short spawnpeds)
{
	if (wincontrol == 0)
	{
		for (int i = 0; i < totalpeds; i++)
		{
			if (PED::IS_PED_DEAD_OR_DYING(missionpeds[i], TRUE) && spawnpeds == 1)
			{
				wincondition += 1;
			}
		}
	}
	if (wincondition == totalpeds)
	{
		MONEY::_MONEY_INCREMENT_CASH_BALANCE(5000, 0x2cd419dc);
		wintimertext = GetTickCount() + 5000;
		wincontrol = 1;
	}
}
