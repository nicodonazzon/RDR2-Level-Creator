#pragma once
#include "script.h"
#include "TextPrint.h"
class Mission_creator
{
private:
public:
	//VARIABLES
	//VARIABLES
	TextPrint textprint;
	static const int totalpeds = 19; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! IF U ADD PEDS CHANGE THIS
	bool checkcombatonce = 0;
	short spawnpeds = 0;
	bool missionstart = 0;
	bool npccords = 0;
	bool wincontrol = 0;
	bool wanted = 0;
	int returncheck = -1;
	int waypoint[totalpeds];
	int key = GetPrivateProfileInt("General", "Whistle", -1, ".\\Mission Creator.ini");
	float heading[totalpeds];
	Ped missionpeds[totalpeds];
	Ped playerped = PLAYER::PLAYER_PED_ID();
	//Vehicle veh1;
	Blip missionblips[totalpeds];
	Vector3 playercoordsinvestigate = ENTITY::GET_ENTITY_COORDS(playerped, TRUE, TRUE);
	Vector3 playercoordsalways = ENTITY::GET_ENTITY_COORDS(playerped, TRUE, TRUE);
	Vector3 playercoordsrun;
	Vector3 pedcoordsorigin[totalpeds];
	Vector3 bushcheckplayer;
	Vector3 bushcheckped[totalpeds];
	DWORD investigatestop = 0;
	DWORD detectiontimertext = 0;
	DWORD deadbodytext = 0;
	DWORD investigetimertext = 0;
	DWORD missiontimertext = 0;
	DWORD wintimertext = 0;
	DWORD horsetimertext = 0;
	//DWORD waittimer[totalpeds];
	//PATROL COORDS
	Vector3 pedswp1[totalpeds];
	Vector3 pedswp2[totalpeds];
	Vector3 pedswp3[totalpeds];

	//Primary functions
	void Set_Coords();
	void Set_Menu();
	void Spawn_Npc();
	void Despawn_Npc();
	void Set_Timers();
	void Set_Win_Condition();
	void Set_Ai();
	//Secondary functions
	void Set_Task();
	//void Set_Npc_Patrol();
	void Set_Alarm();
	void Investige_Npc();
	void Npc_Patrol();
	//Tertiary functions 
	void twopoints(int i);
	void fourpoints(int i);
	void neverwanted(bool wanted);
};

