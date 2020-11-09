#include "Mission_creator.h"
#include "MenuNico.h"
#include "Blips.h"
void Mission_creator::Set_Coords()
{
	if (npccords == 0)
	{
		if (npccords == 0)
		{

			//SET PEDS COORDS

			pedcoordsorigin[0] = { 2493.136475,  -1149.648315,  49.296188 };
			pedcoordsorigin[1] = { 2509.052979,  -1195.330933,  52.477348 };
			pedcoordsorigin[2] = { 2508.394043,  -1209.778320,  52.479897 };
			pedcoordsorigin[3] = { 2505.397705,  -1253.894531,  49.196053 };
			pedcoordsorigin[4] = { 2520.868896,  -1244.520630,  50.031330 };
			pedcoordsorigin[5] = { 2521.498047,  -1247.281860,  50.037945 };
			pedcoordsorigin[6] = { 2527.464111,  -1255.645752,  49.221630 };
			pedcoordsorigin[7] = { 2539.487305,  -1151.660767,  50.532188 };
			pedcoordsorigin[8] = { 2541.253418,  -1237.098145,  53.309788 };
			pedcoordsorigin[9] = { 2555.647705,  -1187.032593,  53.969917 };
			pedcoordsorigin[10] = { 2569.091309,  -1224.562622,  53.311554 };
			pedcoordsorigin[11] = { 2577.566162,  -1202.563477,  53.922581 };
			pedcoordsorigin[12] = { 2593.807129,  -1176.159058,  53.311493 };
			pedcoordsorigin[13] = { 2593.140625,  -1255.435669,  52.667305 };
			pedcoordsorigin[14] = { 2599.263184,  -1150.438232,  51.655632 };
			pedcoordsorigin[15] = { 2627.806641,  -1159.583984,  52.025700 };
			pedcoordsorigin[16] = { 2619.895508,  -1255.194336,  52.626980 };
			pedcoordsorigin[17] = { 2640.620850,  -1182.706055,  53.221313 };
			pedcoordsorigin[18] = { 2643.666992,  -1181.876343,  53.221313 };

			//SET HEADING

			heading[0] = 172.432266;
			heading[1] = 33.620865;
			heading[2] = 139.773499;
			heading[3] = 355.938995;
			heading[4] = 146.718567;
			heading[5] = 47.847134;
			heading[6] = 182.225281;
			heading[7] = 91.990082;
			heading[8] = 19.591284;
			heading[9] = 220.392319;
			heading[10] = 179.373810;
			heading[11] = 83.918259;
			heading[12] = 86.483246;
			heading[13] = 86.628326;
			heading[14] = 175.096375;
			heading[15] = 229.880463;
			heading[16] = 352.371429;
			heading[17] = 217.320709;
			heading[18] = 127.871460;

			//SET WAYPOINTS

			pedswp1[0] = { 2492.715820,  -1256.153687,  49.203545 };
			pedswp1[3] = { 2499.715820,  -1151.153564,  49.268600 };
			pedswp1[7] = { 2516.048828,  -1151.168213,  50.222160 };
			pedswp1[11] = { 2570.944824,  -1196.239258,  53.909031 };
			pedswp1[14] = { 2600.200928,  -1256.947021,  52.667103 };
			pedswp1[16] = { 2621.580811,  -1156.390137,  52.039959 };
			pedswp2[11] = { 2564.331543,  -1202.032471,  53.911610 };
			pedswp3[11] = { 2570.690674,  -1208.393921,  53.914272 };

			for (int i = 1; i < totalpeds;i++)
			{
				waypoint[i] = 0;
			}

			npccords = 1;
		}
	}
}

void Mission_creator::Set_Menu()
{
	MenuNico(missionstart, wanted, spawnpeds, playerped, horsetimertext);
}

void Mission_creator::Spawn_Npc()
{
	if (missionstart == 1
		&& spawnpeds == 0)
	{
		//SET VEHICLE
		DWORD model2 = MISC::GET_HASH_KEY("gatling_gun");
		STREAMING::REQUEST_MODEL(model2, TRUE);
		WAIT(100);
		while (!STREAMING::HAS_MODEL_LOADED(model2))
			WAIT(100);
		//veh1 = VEHICLE::CREATE_VEHICLE(model2, -277.797852, 786.469421, 122.424522, 6.428972, 0, 0, TRUE, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model2);
		//SET PEDS
		DWORD model1 = MISC::GET_HASH_KEY("A_M_M_UniGunslinger_01");
		STREAMING::REQUEST_MODEL(model1, TRUE);
		WAIT(100);
		while (!STREAMING::HAS_MODEL_LOADED(model1))
			WAIT(100);
		for (int i = 0; i < totalpeds; i++)
		{
			missionpeds[i] = PED::CREATE_PED(model1, pedcoordsorigin[i].x, pedcoordsorigin[i].y, pedcoordsorigin[i].z, heading[i], 0, 0, 0, 0);
			PED::_SET_RANDOM_OUTFIT_VARIATION(missionpeds[i], TRUE); //PED VISIBLE
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(missionpeds[i], MISC::GET_HASH_KEY("REL_PLAYER_ENEMY")); //RELATIONSHIOP WITH THE PLAYER
			PED::SET_PED_SEEING_RANGE(missionpeds[i], 25);
			PED::SET_PED_HEARING_RANGE(missionpeds[i], 0);
			PED::SET_PED_ACCURACY(missionpeds[i], 100);
			//TASK::TASK_WANDER_STANDARD(missionpeds[i], 10.0f, 10);
			missionblips[i] = createBlip(missionpeds[i], BLIP_TYPE_BOUNTY_TARGET, BLIP_SPRITE_BOUNTY_TARGET);
		}
		//STOP MODEL STREAM 
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model1);
		Set_Task();
	}
}

void Mission_creator::Despawn_Npc()
{
	//DESPAWN AND RESET ALL
	if (PED::IS_PED_DEAD_OR_DYING(playerped, TRUE)
		|| (GetAsyncKeyState(VK_NEXT)) && (spawnpeds == 1))
	{
		//ENTITY::SET_ENTITY_COORDS(playerped, 1347.719849, -1357.598755, 78.686478, 0, 0, 1, FALSE);
		missiontimertext = 5000 + GetTickCount();
		for (int i = 0; i < totalpeds; i++)
		{
			ENTITY::DELETE_ENTITY(&missionpeds[i]);
			waypoint[i] = 0;
			//waittimer[i] = 0;
		}
		//ENTITY::DELETE_ENTITY(&veh1);
		spawnpeds = 0;
		checkcombatonce = 0;
		missionstart = 0;
		npccords = 0;
		returncheck = -1;
		wincontrol = 0;
		playercoordsinvestigate = { 0,0,0 };
	}
}

void Mission_creator::Set_Task()
{
	//TASKS PEDS

	//PED 1
	TASK::TASK_STAND_GUARD(missionpeds[1], pedcoordsorigin[1].x, pedcoordsorigin[1].y, pedcoordsorigin[1].z, heading[1], "WORLD_HUMAN_BADASS");
	//PED 2
	TASK::TASK_STAND_GUARD(missionpeds[2], pedcoordsorigin[2].x, pedcoordsorigin[2].y, pedcoordsorigin[2].z, heading[2], "WORLD_HUMAN_DRINKING_DRUNK");
	//PED 4
	TASK::TASK_STAND_GUARD(missionpeds[4], pedcoordsorigin[4].x, pedcoordsorigin[4].y, pedcoordsorigin[2].z, heading[4], "WORLD_HUMAN_SMOKE");
	//PED 6
	TASK::TASK_STAND_GUARD(missionpeds[6], pedcoordsorigin[6].x, pedcoordsorigin[6].y, pedcoordsorigin[6].z, heading[6], "WORLD_HUMAN_DRINKING_DRUNK");
	//PED 5
	TASK::TASK_STAND_GUARD(missionpeds[5], pedcoordsorigin[5].x, pedcoordsorigin[5].y, pedcoordsorigin[5].z, heading[5], "WORLD_HUMAN_BADASS");
	//PED 8
	TASK::TASK_STAND_GUARD(missionpeds[8], pedcoordsorigin[8].x, pedcoordsorigin[8].y, pedcoordsorigin[8].z, heading[8], "WORLD_HUMAN_SMOKE");
	//PED 9
	TASK::TASK_STAND_GUARD(missionpeds[9], pedcoordsorigin[9].x, pedcoordsorigin[9].y, pedcoordsorigin[9].z, heading[9], "WORLD_HUMAN_BADASS");
	//PED 10
	TASK::TASK_STAND_GUARD(missionpeds[10], pedcoordsorigin[10].x, pedcoordsorigin[10].y, pedcoordsorigin[10].z, heading[10], "WORLD_HUMAN_BADASS");
	//PED 12
	TASK::TASK_STAND_GUARD(missionpeds[12], pedcoordsorigin[12].x, pedcoordsorigin[12].y, pedcoordsorigin[12].z, heading[12], "WORLD_HUMAN_BADASS");
	//PED 13
	TASK::TASK_STAND_GUARD(missionpeds[13], pedcoordsorigin[13].x, pedcoordsorigin[13].y, pedcoordsorigin[13].z, heading[13], "WORLD_HUMAN_SMOKE");
	//PED 16
	TASK::TASK_STAND_GUARD(missionpeds[15], pedcoordsorigin[15].x, pedcoordsorigin[15].y, pedcoordsorigin[15].z, heading[15], "WORLD_HUMAN_SMOKE");
	//PED 17
	TASK::TASK_STAND_GUARD(missionpeds[17], pedcoordsorigin[17].x, pedcoordsorigin[17].y, pedcoordsorigin[17].z, heading[17], "WORLD_HUMAN_SMOKE");
	//PED 17
	TASK::TASK_STAND_GUARD(missionpeds[18], pedcoordsorigin[18].x, pedcoordsorigin[18].y, pedcoordsorigin[18].z, heading[18], "WORLD_HUMAN_BADASS");
	spawnpeds = 1;
}

/*void Mission_creator::Set_Npc_Patrol()
{
	//PED 0
	Npc_Patrol();
	//PED 1
	//PED 5
	//PED 11
	//PED 14
	//PED 15
	//PED 18
}*/

void Mission_creator::Set_Alarm()
{
	for (int i = 0; i < totalpeds; i++)
	{
		if (PED::IS_PED_IN_COMBAT(missionpeds[i], playerped) && PED::IS_PED_SHOOTING(missionpeds[i]))
		{
			detectiontimertext = 3000 + GetTickCount();
			for (int j = 0; j < totalpeds; j++)
			{
				TASK::TASK_COMBAT_PED(missionpeds[j], playerped, 0, 0);
			}
			checkcombatonce = 1;
		}
		//Body found alarm
		if (PED::IS_PED_DEAD_OR_DYING(missionpeds[i], TRUE) || PED::_IS_PED_HOGTIED(missionpeds[i]))
		{
			for (int g = 0; g < totalpeds; g++)
			{
				if (!PED::_IS_PED_HOGTIED(missionpeds[g]) && !PED::IS_PED_DEAD_OR_DYING(missionpeds[g], TRUE))
				{
					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(missionpeds[g], missionpeds[i], 17)
						&& deadbodytext < GetTickCount())
					{
						deadbodytext = 3000 + GetTickCount();
						TASK::TASK_COMBAT_PED(missionpeds[g], playerped, 0, 0);
						break;
					}
				}
			}
		}
	}
}

void Mission_creator::Investige_Npc()
{
	playercoordsalways = ENTITY::GET_ENTITY_COORDS(playerped, TRUE, TRUE);
	for (int i = 0; i < totalpeds; i++)
	{
		if (returncheck == -1)
		{
			if (GetAsyncKeyState(key) 
				&& investigatestop < GetTickCount()
				&& ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], playercoordsalways.x - 15, playercoordsalways.y - 15, playercoordsalways.z - 15, playercoordsalways.x + 15, playercoordsalways.y + 15, playercoordsalways.z + 15, false, false, false))
			{
				playercoordsinvestigate = ENTITY::GET_ENTITY_COORDS(playerped, TRUE, TRUE);
				if (!PED::IS_PED_DEAD_OR_DYING(missionpeds[i], TRUE) && !PED::_IS_PED_HOGTIED(missionpeds[i]))
				{
					investigatestop = 20000 + GetTickCount();
					investigetimertext = 5000 + GetTickCount();
					TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], playercoordsinvestigate.x, playercoordsinvestigate.y, playercoordsinvestigate.z, 1, 0, 0, 0, 0);
					returncheck = i;
					break;
				}
			}
		}
	}

	if (investigatestop == GetTickCount())
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[returncheck], pedcoordsorigin[returncheck].x, pedcoordsorigin[returncheck].y, pedcoordsorigin[returncheck].z, 1, 0, 0, 0, 0);
		returncheck = -1;
	}
}

void Mission_creator::Npc_Patrol()
{
	for (int i = 0; i < totalpeds;i++)
	{
		for (int i = 0; i < 17;i++)
		{
			twopoints(i);
		}
		fourpoints(11);
	}
}

void Mission_creator::Set_Timers()
{
	//HORSE TIMER TEXT
	if (horsetimertext > GetTickCount())
	{
		const char* text;
		text = "Please, get down the ~COLOR_BLUE~horse~COLOR_WHITE~ before you start the mission.";
		textprint.ShowSubtitle(text);
	}
	//DETECT TIMER TEXT
	if (detectiontimertext > GetTickCount()
		&& deadbodytext < GetTickCount())
	{
		const char* text;
		text = "They know you are here.~COLOR_RED~ Watch out~COLOR_WHITE~!";
		textprint.ShowSubtitle(text);
	}
	//DETECT TIMER TEXT
	if (deadbodytext > GetTickCount())
	{
		const char* text;
		text = "The enemy found a dead body.~COLOR_RED~ Look out~COLOR_WHITE~!";
		textprint.ShowSubtitle(text);
	}
	//SHOOT TIMER TEXT
	if (investigetimertext > GetTickCount())
	{
		const char* text;
		text = "The enemies are ~COLOR_RED~investigating~COLOR_WHITE~! Cooldown of 20 seg.";
		textprint.ShowSubtitle(text);
	}
	//finish mission text
	if (missiontimertext > GetTickCount())
	{
		const char* text;
		text = "The mission is over. You can restart in the menu.";
		textprint.ShowSubtitle(text);
	}
	//WIN mission text
	if (wintimertext > GetTickCount())
	{
		const char* text;
		text = "Congratulations, you ~COLOR_BLUE~Win~COLOR_WHITE~!";
		textprint.ShowSubtitle(text);
	}
}

void Mission_creator::Set_Win_Condition()
{
	int wincondition = 0;
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

void Mission_creator::Set_Ai()
{
	//START AI
	if (checkcombatonce == 0)
	{
			//ALARM 
			Set_Alarm();
			//INVESTIGATE WHISTLE
			Investige_Npc();
			//PATROL
			Npc_Patrol();
			//WANTED
			neverwanted(wanted);
	}
	//END AI
}

void Mission_creator::twopoints(int i)
{
	if (i == 0 || i == 3 || i == 7 || i == 14 || i == 16)
	{
		//GO TO WP1
		if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedcoordsorigin[i].x - 1, pedcoordsorigin[i].y - 1, pedcoordsorigin[i].z - 1, pedcoordsorigin[i].x + 1, pedcoordsorigin[i].y + 1, pedcoordsorigin[i].z + 1, false, false, false)
			&& waypoint[i] == 0)
		{
			waypoint[i] = 1;
			//waittimer[i] = 5000 + GetTickCount();
			TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp1[i].x, pedswp1[i].y, pedswp1[i].z, 1, 0, 0, 0, 0);
		}
		/*if (waittimer[i] == GetTickCount()
			&& waypoint[i] == 1)
		{
			TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp1[i].x, pedswp1[i].y, pedswp1[i].z, 1, 0, 0, 0, 0);
		}*/
		//GO TO ORIGIN
		if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedswp1[i].x - 1, pedswp1[i].y - 1, pedswp1[i].z - 1, pedswp1[i].x + 1, pedswp1[i].y + 1, pedswp1[i].z + 1, false, false, false)
			&& waypoint[i] == 1)
		{
			waypoint[i] = 0;
			//waittimer[i] = 5000 + GetTickCount();
			TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedcoordsorigin[i].x, pedcoordsorigin[i].y, pedcoordsorigin[i].z, 1, 0, 0, 0, 0);
		}
		/*if (waittimer[i] == GetTickCount()
			&& waypoint[i] == 0)
		{
			TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedcoordsorigin[i].x, pedcoordsorigin[i].y, pedcoordsorigin[i].z, 1, 0, 0, 0, 0);
		}*/
	}
}

void Mission_creator::fourpoints(int i)
{
	//GO TO WP1
	if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedcoordsorigin[i].x - 1, pedcoordsorigin[i].y - 1, pedcoordsorigin[i].z - 1, pedcoordsorigin[i].x + 1, pedcoordsorigin[i].y + 1, pedcoordsorigin[i].z + 1, false, false, false)
		&& waypoint[i] == 0)
	{
		waypoint[i] = 1;
		//waittimer[i] = 5000 + GetTickCount();
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp1[i].x, pedswp1[i].y, pedswp1[i].z, 1, 0, 0, 0, 0);
	}
	/*if (waittimer[i] == GetTickCount()
		&& waypoint[i] == 1)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp1[i].x, pedswp1[i].y, pedswp1[i].z, 1, 0, 0, 0, 0);
	}*/
	//GO TO WP2
	if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedswp1[i].x - 1, pedswp1[i].y - 1, pedswp1[i].z - 1, pedswp1[i].x + 1, pedswp1[i].y + 1, pedswp1[i].z + 1, false, false, false)
		&& waypoint[i] == 1)
	{
		waypoint[i] = 2;
		//waittimer[i] = 5000 + GetTickCount();
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp2[i].x, pedswp2[i].y, pedswp2[i].z, 1, 0, 0, 0, 0);
	}
	/*if (waittimer[i] == GetTickCount()
		&& waypoint[i] == 2)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp2[i].x, pedswp2[i].y, pedswp2[i].z, 1, 0, 0, 0, 0);
	}*/
	//GO TO WP3
	if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedswp2[i].x - 1, pedswp2[i].y - 1, pedswp2[i].z - 1, pedswp2[i].x + 1, pedswp2[i].y + 1, pedswp2[i].z + 1, false, false, false)
		&& waypoint[i] == 2)
	{
		waypoint[i] = 3;
		//waittimer[i] = 5000 + GetTickCount();
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp3[i].x, pedswp3[i].y, pedswp3[i].z, 1, 0, 0, 0, 0);
	}
	/*if (waittimer[i] == GetTickCount()
		&& waypoint[i] == 3)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedswp3[i].x, pedswp3[i].y, pedswp3[i].z, 1, 0, 0, 0, 0);
	}*/
	//GO TO ORIGIN
	if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], pedswp3[i].x - 1, pedswp3[i].y - 1, pedswp3[i].z - 1, pedswp3[i].x + 1, pedswp3[i].y + 1, pedswp3[i].z + 1, false, false, false)
		&& waypoint[i] == 3)
	{
		waypoint[i] = 0;
		//waittimer[i] = 5000 + GetTickCount();
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedcoordsorigin[i].x, pedcoordsorigin[i].y, pedcoordsorigin[i].z, 1, 0, 0, 0, 0);
	}
	/*if (waittimer[i] == GetTickCount()
		&& waypoint[i] == 0)
	{
		TASK::TASK_GO_TO_COORD_ANY_MEANS(missionpeds[i], pedcoordsorigin[i].x, pedcoordsorigin[i].y, pedcoordsorigin[i].z, 1, 0, 0, 0, 0);
	}*/
}

void Mission_creator::neverwanted(bool wanted)
{
	if (wanted == 1)
	{
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0f);
	}
	else
	{
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(1.0f);
	}
}
