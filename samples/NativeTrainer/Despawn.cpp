#include "Despawn.h"
#include "scriptmenu.h"

void Despawn(Ped playerped, short spawnpeds, int* pedhogtie, DWORD& missiontimertext, int totalpeds, Ped* missionpeds, Vehicle& veh1, 
	bool& checkcombatonce, bool& npccords, int& returncheck, bool& wincontrol, bool& returntimercheck, Vector3& playercoordsinvestigate)
{

	if ((PED::IS_PED_DEAD_OR_DYING(playerped, TRUE)
		|| GetAsyncKeyState(VK_NEXT)) && (spawnpeds == 1))
	{
		ENTITY::SET_ENTITY_COORDS(playerped, 1347.719849, -1357.598755, 78.686478, 0, 0, 1, FALSE);
		missiontimertext = 5000 + GetTickCount();
		for (int i = 0; i < totalpeds; i++)
		{
			ENTITY::DELETE_ENTITY(missionpeds);
			*pedhogtie = -1;
			missionpeds++;
			pedhogtie++;
		}
		ENTITY::DELETE_ENTITY(&veh1);
		spawnpeds = 0;
		checkcombatonce = 0;
		npccords = 0;
		returncheck = -1;
		wincontrol = 0;
		returntimercheck = 0;
		playercoordsinvestigate = { 0,0,0 };
	}
}
