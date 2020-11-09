#include "Spawn_Npc.h"
#include "scriptmenu.h"
#include "blips.h"
void Spawn_Npc(int totalpeds, Ped playerped, Ped* missionpeds, short& spawnpeds, Vehicle& veh1, Vector3* pedcoordsorigin, float* heading, Blip* missionblips)
{
	if ((ENTITY::IS_ENTITY_IN_AREA(playerped, -436.585999, 683.315979, 112.486687, -241.001190, 866.846313, 127.775734, false, false, false))
		&& spawnpeds == 0)
	{
		//SET VEHICLE
		DWORD model2 = MISC::GET_HASH_KEY("gatling_gun");
		STREAMING::REQUEST_MODEL(model2, TRUE);
		WAIT(100);
		while (!STREAMING::HAS_MODEL_LOADED(model2))
			WAIT(100);
		veh1 = VEHICLE::CREATE_VEHICLE(model2, -277.797852, 786.469421, 122.424522, 6.428972, 0, 0, TRUE, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model2);
		//SET PEDS
		DWORD model1 = MISC::GET_HASH_KEY("A_M_M_UniGunslinger_01");
		STREAMING::REQUEST_MODEL(model1, TRUE);
		WAIT(100);
		while (!STREAMING::HAS_MODEL_LOADED(model1))
			WAIT(100);
		for (int i = 0; i < totalpeds; i++)
		{
			*missionpeds = PED::CREATE_PED(model1, pedcoordsorigin->x, pedcoordsorigin->y, pedcoordsorigin->z, *heading, 0, 0, 0, 0);
			PED::_SET_RANDOM_OUTFIT_VARIATION(*missionpeds, TRUE); //PED VISIBLE
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(*missionpeds, MISC::GET_HASH_KEY("REL_PLAYER_ENEMY")); //RELATIONSHIOP WITH THE PLAYER
			PED::SET_PED_SEEING_RANGE(*missionpeds, 20);
			PED::SET_PED_HEARING_RANGE(*missionpeds, 0);
			PED::SET_PED_ACCURACY(*missionpeds, 100);
			//TASK::TASK_WANDER_STANDARD(missionpeds[i], 10.0f, 10);
			*missionblips = createBlip(*missionpeds, BLIP_TYPE_BOUNTY_TARGET, BLIP_SPRITE_BOUNTY_TARGET);
			missionpeds++;
			missionblips++;
			pedcoordsorigin++;
			heading++;
		}
		//STOP MODEL STREAM 
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model1);
	}

}