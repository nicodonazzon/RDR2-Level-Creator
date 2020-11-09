#include "TestingCodes.h"

/*//RETUR TO ORIGIN AFTER INVESTIGATE (PART OF INVESTIGATE CODE)
if (returncheck > -1)
{
	if (PED::IS_PED_DEAD_OR_DYING(missionpeds[returncheck], TRUE))
	{
		returncheck = -1;
	}
	if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[returncheck], playercoordsinvestigate.x - 2, playercoordsinvestigate.y - 2, playercoordsinvestigate.z - 2, playercoordsinvestigate.x + 2, playercoordsinvestigate.y + 2, playercoordsinvestigate.z + 2, false, false, false)
		&& returntimercheck == 0)
	{
		//HACER TIMER VAGO
		//WAIT(4000);
		returntimer->Start();
		investigatestop = 10000 + GetTickCount();
		returntimercheck = 1;
		//TASK::TASK_WANDER_STANDARD(missionpeds[returncheck], 10.0f, 10);
	}
	if (returntimer->GetDuration() > 5
		&& ENTITY::IS_ENTITY_IN_AREA(missionpeds[returncheck], playercoordsinvestigate.x - 1, playercoordsinvestigate.y - 1, playercoordsinvestigate.z - 1, playercoordsinvestigate.x + 1, playercoordsinvestigate.y + 1, playercoordsinvestigate.z + 1, false, false, false))
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[returncheck], pedcoordsorigin[returncheck].x, pedcoordsorigin[returncheck].y, pedcoordsorigin[returncheck].z, 1, 0, 0, 0, 0);
		returncheck = -1;
		returntimercheck = 0;
	}
}*/
