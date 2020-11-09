#pragma once
#include "Alarm.h"
#include "scriptmenu.h"
void Alarm(bool& checkcombatonce, int* pedhogtie, int totalpeds, Ped* missionpeds, Ped* missionpeds2, Ped playerped, DWORD& deadbodytext, DWORD& detectiontimertext, Vector3 playercoordsalways)
{
	for (int i = 0; i < totalpeds; i++)
	{
		//HOGTIE CHECK
		if (ENTITY::IS_ENTITY_IN_AREA(*missionpeds, playercoordsalways.x - 1, playercoordsalways.y - 1, playercoordsalways.z - 1, playercoordsalways.x + 1, playercoordsalways.y + 1, playercoordsalways.z + 1, false, false, false)
			&& *pedhogtie != i + 1)
		{
			*pedhogtie = i + 1;
		}

		//ALARM SHOOT NPC

		if (PED::IS_PED_SHOOTING(*missionpeds))
		{
			detectiontimertext = 3000 + GetTickCount();
			for (int j = 0; j < totalpeds; j++)
			{
				TASK::TASK_COMBAT_PED(*missionpeds2, playerped, 0, 0);
				missionpeds2++;
			}
			checkcombatonce = 1;

		}
		//ALARM IF FOUND BODY
		if (*pedhogtie == i + 1 || PED::IS_PED_DEAD_OR_DYING(missionpeds[i], TRUE))
		{
			for (int g = 0; g < totalpeds; g++)
			{
				if (g != i && !PED::IS_PED_DEAD_OR_DYING(missionpeds[g], TRUE))
				{
					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(missionpeds[g], missionpeds[i], 17)
						&& deadbodytext < GetTickCount())
					{
						deadbodytext = 3000 + GetTickCount();
						TASK::TASK_COMBAT_PED(missionpeds[g], playerped, 0, 0);
						break;
					}
					/*if (!ENTITY::IS_ENTITY_IN_WATER(missionpeds[i]))
					{
						if ((ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(missionpeds[g], missionpeds[i], 17)
							&& !ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], bushcheckped[i].x - 3, bushcheckped[i].y - 3, bushcheckped[i].z - 3, bushcheckped[i].x + 3, bushcheckped[i].y + 3, bushcheckped[i].z + 3, false, false, false))
							|| (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(missionpeds[g], missionpeds[i], 17) && ENTITY::IS_ENTITY_IN_AREA(missionpeds[g], bushcheckped[i].x - 1, bushcheckped[i].y - 1, bushcheckped[i].z - 1, bushcheckped[i].x + 1, bushcheckped[i].y + 1, bushcheckped[i].z + 1, false, false, false)))
						{
							TASK::TASK_COMBAT_PED(missionpeds[g], playerped, 0, 0);
							break;
						}
					}*/
				}
			}
		}
		pedhogtie++;
		missionpeds++;
	}
}
