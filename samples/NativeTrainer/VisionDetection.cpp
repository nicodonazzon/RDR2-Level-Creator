#include "VisionDetection.h"
#include "scriptmenu.h"
void Vision_Detection(int totalpeds, Ped* missionpeds, Ped playerped)
{
	for (int i = 0; i < totalpeds; i++)
	{
		if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(*missionpeds, playerped, 17)
			//&& !ENTITY::IS_ENTITY_IN_AREA(playerped, bushcheckplayer.x - 3, bushcheckplayer.y - 3, bushcheckplayer.z - 3, bushcheckplayer.x + 3, bushcheckplayer.y + 3, bushcheckplayer.z + 3, false, false, false)
			&& !PED::IS_PED_IN_COMBAT(*missionpeds, playerped))
		{
			TASK::TASK_COMBAT_PED(*missionpeds, playerped, 0, 0);
		}
		missionpeds++;
	}
}
