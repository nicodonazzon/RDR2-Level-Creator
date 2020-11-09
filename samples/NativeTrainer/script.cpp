/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "script.h"
#include "Mission_creator.h"
using namespace std;

void main()
{
	Mission_creator stdenis;
	while (true)
	{
		stdenis.Set_Coords();
		stdenis.Set_Menu();
		stdenis.Spawn_Npc();
		stdenis.Despawn_Npc();
		stdenis.Set_Timers();
		stdenis.Set_Ai();
		stdenis.Set_Win_Condition();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}