#pragma once
#include "script.h"
Hash joaat(const char* string)
{
	return MISC::GET_HASH_KEY(string);
}

void DrawSprite(const char* category, const char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a)
{
	float fX = x + scalex / 2;
	float fY = y + scaley / 2;
	if (!TXD::HAS_STREAMED_TEXTURE_DICT_LOADED(sprite))
		TXD::REQUEST_STREAMED_TEXTURE_DICT(sprite, 0);
	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scalex, scaley, rotation, r, g, b, a, 1);
	TXD::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void draw_Text(const char* text, float x, float y, int r, int g, int b, int a, bool centered = false, float sx = 0.342f, float sy = 0.342f)
{
	HUD::_SET_TEXT_COLOR(r, g, b, a);
	HUD::SET_TEXT_SCALE(sx, sy);
	HUD::SET_TEXT_CENTRE(centered);
	const char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	HUD::_DISPLAY_TEXT(literalString, x, y);
}

void drawRect(float x, float y, float width, float height, int r, int g, int b, int a)
{
	float fX = x + width / 2;
	float fY = y + height / 2;
	GRAPHICS::DRAW_RECT(fX, fY, width, height, r, g, b, a, true, true);
}

void PrintSubtitle(const char* text)
{
	const char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(literalString);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}
//MENU CONSTRUCTOR

enum Submenus {
	Closed,
	Main_Menu,
	Submenu1,
	Submenu2,
	DogSpawner_Menu,
};


int submenu = 0;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
int lastSubmenuMinOptions[20];
int lastSubmenuMaxOptions[20];
int currentOption;
int optionCount;
int maxOptions = 8;
bool optionPress = false;
int currentMenuMaxOptions = maxOptions;
int currentMenuMinOptions = 1;
bool leftPress = false;
bool rightPress = false;
bool fastLeftPress = false;
bool fastRightPress = false;
float menuX = 0.052f;
bool menuHeader = false;

void NULLVOID() {}

void CloseMenu()
{
	submenu = Closed;
	submenuLevel = 0;
	currentOption = 1;
}

void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	lastSubmenuMinOptions[submenuLevel] = currentMenuMinOptions;
	lastSubmenuMaxOptions[submenuLevel] = currentMenuMaxOptions;
	currentOption = 1;
	currentMenuMinOptions = 1;
	currentMenuMaxOptions = maxOptions;
	submenu = newSubmenu;
	submenuLevel++;
	optionPress = false;
}

void addTitle(const char* title) {
	optionCount = 0;
	draw_Text(title, menuX + 0.13f, 0.076f, 255, 255, 255, 255, true, 0.5f, 0.5f);
	drawRect(menuX, 0.053f, 0.260f, 0.104f, 0, 0, 0, 190);
	DrawSprite("generic_textures", "menu_header_1a", menuX, 0.058f, 0.260f, 0.074f, 0, 255, 255, 255, 255);
	DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.131f + 0.027f, 0.260f, 0.002f, 0, 255, 255, 255, 255);
}

void addHeader(const char* header)
{
	menuHeader = true;
	draw_Text(header, menuX + 0.13f, 0.076f + 0.0575f, 255, 255, 255, 255, true, 0.3f, 0.3f);
}

float bodyOffset = 0;

void addOption3(const char* option, void (func)(bool& wanted), bool& wanted) {
	optionCount++;
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		draw_Text(option, menuX + 0.007f, 0.131f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 255, 255, 255, 255);
		drawRect(menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		if (currentOption == optionCount) {
			DrawSprite("generic_textures", "selection_box_bg_1d", menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 255, 0, 0, 190);
			if (optionPress)
				func(wanted);
		}
	}
}

void addOption2(const char* option, void (func)(bool& missionstart, short& spawnpeds, Ped& playerped, DWORD& horsetimertext), bool& missionstart, short& spawnpeds, Ped& playerped, DWORD& horsetimertext) {
	optionCount++;
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		draw_Text(option, menuX + 0.007f, 0.131f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 255, 255, 255, 255);
		drawRect(menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		if (currentOption == optionCount) {
			DrawSprite("generic_textures", "selection_box_bg_1d", menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 255, 0, 0, 190);
			if (optionPress)
				func(missionstart, spawnpeds, playerped, horsetimertext);
		}
	}
}

void addOption(const char* option, void (func)() = NULLVOID) {
	optionCount++;
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		draw_Text(option, menuX + 0.007f, 0.131f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 255, 255, 255, 255);
		drawRect(menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		if (currentOption == optionCount) {
			DrawSprite("generic_textures", "selection_box_bg_1d", menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 255, 0, 0, 190);
			if (optionPress)
				func();
		}
	}
}

void addSubmenuOption(const char* option, int submenu) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		DrawSprite("menu_textures", "selection_arrow_right", menuX + 0.235f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.01125f, 0.02f, 0, 255, 255, 255, 255);
		if (currentOption == optionCount)
			if (optionPress)
				changeSubmenu(submenu);
	}
}
void addSubmenuOption(const char* option, int submenu, void (func)()) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		DrawSprite("menu_textures", "selection_arrow_right", menuX + 0.235f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.01125f, 0.02f, 0, 255, 255, 255, 255);
		if (currentOption == optionCount) {
			if (optionPress) {
				func();
				changeSubmenu(submenu);
			}
		}
	}
}

void addBoolOption2(const char* option, short var, void (func)() = NULLVOID) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		if (var) {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
			DrawSprite("generic_textures", "tick", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		else {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		if (currentOption == optionCount)
			if (optionPress)
				func();
	}
}

void addBoolOption(const char* option, bool var, void (func)() = NULLVOID) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		if (var) {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
			DrawSprite("generic_textures", "tick", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		else {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		if (currentOption == optionCount)
			if (optionPress)
				func();
	}
}

void addIntOption(const char* option, int* var, int step = 1, bool fastPress = false, int min = -2147483647, int max = 2147483647) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %i >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
	}
}
void addIntOption(const char* option, int* var, void (func)(), int step = 1, bool fastPress = false, int min = -2147483647, int max = 2147483647) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %i >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		if (optionPress)
			func();
	}
}

void addFloatOption(const char* option, float* var, float step, bool fastPress = false, float min = -3.4028235e38, float max = 3.4028235e38) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %.03f >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
	}
}
void addFloatOption(const char* option, float* var, float step, void (func)(), bool fastPress = false, float min = -3.4028235e38, float max = 3.4028235e38) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %.03f >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		if (optionPress)
			func();
	}
}

void addStringOption(const char* option, const char* var, int* intvar, int elementCount, bool fastPress = false) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %s >", option, var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress == false)
		{
			if (leftPress) {
				if (*intvar <= 0)
					*intvar = elementCount;
				else
					*intvar -= 1;
			}
			else if (rightPress)
			{
				if (*intvar >= elementCount)
					*intvar = 0;
				else
					*intvar += 1;
			}
		}
		else
		{
			if (fastLeftPress) {
				if (*intvar <= 0)
					*intvar = elementCount;
				else
					*intvar -= 1;
			}
			else if (fastRightPress)
			{
				if (*intvar >= elementCount)
					*intvar = 0;
				else
					*intvar += 1;
			}
		}
	}
}
void addStringOption(const char* option, const char* var, int* intvar, int elementCount, void (func)(), bool fastPress = false) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %s >", option, var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress == false)
		{
			if (leftPress) {
				if (*intvar <= 0)
					*intvar = elementCount;
				else
					*intvar -= 1;
			}
			else if (rightPress)
			{
				if (*intvar >= elementCount)
					*intvar = 0;
				else
					*intvar += 1;
			}
		}
		else
		{
			if (fastLeftPress) {
				if (*intvar <= 0)
					*intvar = elementCount;
				else
					*intvar -= 1;
			}
			else if (fastRightPress)
			{
				if (*intvar >= elementCount)
					*intvar = 0;
				else
					*intvar += 1;
			}
		}
		if (optionPress)
			func();
	}
}

void displayOptionIndex() {
	char buffer[32];
	snprintf(buffer, 32, "%i of %i", currentOption, optionCount);
	if (optionCount >= maxOptions) {
		draw_Text(buffer, menuX + 0.13f, 0.131f + (0.038f * (maxOptions + 1)), 255, 255, 255, 255, true);
		drawRect(menuX, 0.124f + (0.038f * (maxOptions + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.126f + (0.038f * (maxOptions + 1)), 0.260f, 0.002f, 0, 255, 255, 255, 255);
	}
	else {
		draw_Text(buffer, menuX + 0.13f, 0.131f + (0.038f * (optionCount + 1)), 255, 255, 255, 255, true);
		drawRect(menuX, 0.124f + (0.038f * (optionCount + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.126f + (0.038f * (optionCount + 1)), 0.260f, 0.002f, 0, 255, 255, 255, 255);
	}
}

void resetVars()
{
	if (submenu != Closed) {
		displayOptionIndex();
	}
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	menuHeader = false;
}

void ButtonMonitoring()
{
	if (submenu == Closed)
	{
		if (PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LT")) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LT")))
		{
			//INPUT_FRONTEND_LT
			//INPUT_SELECT_CHARACTER_TREVOR
			submenu = Main_Menu;
			submenuLevel = 0;
			currentOption = 1;
			currentMenuMinOptions = 1;
			currentMenuMaxOptions = maxOptions;
		}
	}
	else
	{
		if (PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RDOWN"))) { //Enter
			optionPress = true;
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RRIGHT"))) //Backspace
		{
			if (submenu == Main_Menu) {
				CloseMenu();
			}
			else
			{
				submenu = lastSubmenu[submenuLevel - 1];
				currentOption = lastOption[submenuLevel - 1];
				currentMenuMinOptions = lastSubmenuMinOptions[submenuLevel - 1];
				currentMenuMaxOptions = lastSubmenuMaxOptions[submenuLevel - 1];
				submenuLevel--;
			}
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_UP"))) //Scroll Up
		{
			if (currentOption == 1)
			{
				currentOption = optionCount;
				currentMenuMaxOptions = optionCount;
				if (optionCount > maxOptions)
					currentMenuMinOptions = optionCount - maxOptions + 1;
				else
					currentMenuMinOptions = 1;
			}
			else
			{
				currentOption--;
				if (currentOption < currentMenuMinOptions) {
					currentMenuMinOptions = currentOption;
					currentMenuMaxOptions = currentOption + maxOptions - 1;
				}
			}
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_DOWN"))) //Scroll Down
		{
			if (currentOption == optionCount)
			{
				currentOption = 1;
				currentMenuMinOptions = 1;
				currentMenuMaxOptions = maxOptions;
			}
			else
			{
				currentOption++;
				if (currentOption > currentMenuMaxOptions) {
					currentMenuMaxOptions = currentOption;
					currentMenuMinOptions = currentOption - maxOptions + 1;
				}
			}
		}

		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LEFT"))) //Scroll Left
		{
			leftPress = true;
		}
		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RIGHT"))) //Scroll Right
		{
			rightPress = true;
		}

		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LEFT"))) {
			fastLeftPress = true;
		}
		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RIGHT"))) {
			fastRightPress = true;
		}
	}
}
//MENU FUNCTIONS
void EnableMission(bool& missionstart, short& spawnpeds, Ped& playerped, DWORD& horsetimertext)
{
	//int startpoint = rand() % 3;
	if (PED::IS_PED_ON_MOUNT(playerped))
	{
		horsetimertext = 3000 + GetTickCount();
	}
	else
	{
		/*if (startpoint == 0)
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -386.844330, 765.241882, 115.870644, 0, 0, 1, FALSE);
		if (startpoint == 1)
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -306.080963, 816.934448, 118.980942, 0, 0, 1, FALSE); //CHANGE TO OTHER COORD IF U WANT, MORE REPLAYABILITY
		if (startpoint == 2)
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -296.258362, 847.071960, 120.030159, 0, 0, 1, FALSE);
		if (startpoint == 3)
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -216.959091, 809.962463, 124.596321, 0, 0, 1, FALSE);*/
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 2660.230469, -1213.233154, 53.368267, 0, 0, 1, FALSE);
		missionstart = 1;
		spawnpeds = 0;
	}
	CloseMenu();
}

void EnableWanted(bool& wanted)
{
	wanted = 0;
}

void DisableWanted(bool& wanted)
{
	wanted = 1;
}

void MenuNico(bool& missionstart, bool& wanted, short& spawnpeds, Ped& playerped, DWORD& horsetimertext)
{
	ButtonMonitoring();
	switch (submenu)
	{
	case Main_Menu:
		addTitle("Bounty hunters in the town");
		addHeader("Mission by Nicotuky. Menu by Raon Hook.");
		//addSubmenuOption("Submenu 1", Submenu1, [] { PrintSubtitle("This subtitle was called before the menu changed\nUseful when needing to initialize something beforehand"); });
		//addBoolOption("Godmode", Godmode, [] {Godmode = !Godmode; });
		//addBoolOption("Invisibility", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()), [] {ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); });
		addOption2("Start Mission", EnableMission, missionstart, spawnpeds, playerped, horsetimertext);
		if (wanted == 0)
		{
			addOption3("Disable Wanted while in mission", DisableWanted, wanted);
		}
		else if (wanted == 1)
		{
			addOption3("Enable Wanted while in mission", EnableWanted, wanted);
		}
		//addFloatOption("Set Player Scale", &playerScale, 0.1f, SetPlayerScale);
		//addOption("Teleport Forward", TeleportForward);
		//addStringOption("String Option", strings[stringoptionint], &stringoptionint, ARRAYSIZE(strings) - 1, [] {PrintSubtitle(strings[stringoptionint]); });
		break;
		/*case Submenu1:
			addTitle("Submenu 1");
			addOption("Option");
			addSubmenuOption("Dog Spawner", DogSpawner_Menu);
			break;
		case DogSpawner_Menu:
			addTitle("Dog Spawner");
			for (int i = 0; i < ARRAYSIZE(Dogs); i++) //Increase int i until i == element count of Dogs[]
			{
				addOption(Dogs[i].name, [] { //Adds an option for every loop and Iterates through Dogs with value of i
					Hash model = GAMEPLAY::GET_HASH_KEY(Dogs[currentOption - 1].model); //You can't pass i through to the function so you must use currentOption - 1 (must subtract 1, as first option = 1, but element 1 of an array = 0)
					CreatePed(model); //Creates ped										//(If you had added an option before the for loop, you would use currentOption - 2, as optionCount would've Increased by 1)
					});
			}
			break;*/
	}
	resetVars();
}
