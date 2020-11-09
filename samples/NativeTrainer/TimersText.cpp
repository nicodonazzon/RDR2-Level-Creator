#include "TimersText.h"

void showSubtitle(const char* text)
{
	UILOG::_UILOG_SET_CACHED_OBJECTIVE((const char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text)); // _UILOG_SET_CACHED_OBJECTIVE
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE(); // _UILOG_PRINT_CACHED_OBJECTIVE
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE(); // _UILOG_CLEAR_CACHED_OBJECTIVE
}

void TimersText(DWORD& deadbodytext, DWORD& detectiontimertext, DWORD& horsetimertext, DWORD& investigetimertext, DWORD& missiontimertext, DWORD& wintimertext)
{
	//HORSE TIMER TEXT
	if (horsetimertext > GetTickCount())
	{
		const char* text;
		text = "Please, get down the ~COLOR_BLUE~horse~COLOR_WHITE~ before you start the mission.";
		showSubtitle(text);
	}
	//DETECT TIMER TEXT
	if (detectiontimertext > GetTickCount()
		&& deadbodytext < GetTickCount())
	{
		const char* text;
		text = "They know you are here.~COLOR_RED~ Watch out~COLOR_WHITE~!";
		showSubtitle(text);
	}
	//DETECT TIMER TEXT
	if (deadbodytext > GetTickCount())
	{
		const char* text;
		text = "The enemy found a dead body.~COLOR_RED~ Look out~COLOR_WHITE~!";
		showSubtitle(text);
	}
	//SHOOT TIMER TEXT
	if (investigetimertext > GetTickCount())
	{
		const char* text;
		text = "The enemies are ~COLOR_RED~investigating~COLOR_WHITE~! Cooldown of 20 seg.";
		showSubtitle(text);
	}
	//finish mission text
	if (missiontimertext > GetTickCount())
	{
		const char* text;
		text = "The mission is over. You can restart in the menu.";
		showSubtitle(text);
	}
	//WIN mission text
	if (wintimertext > GetTickCount())
	{
		const char* text;
		text = "Congratulations, you ~COLOR_BLUE~Win~COLOR_WHITE~!";
		showSubtitle(text);
	}
}
