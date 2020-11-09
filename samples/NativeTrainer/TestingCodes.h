//DANGER MENSSAGE

/*struct text_box_t
{
	std::string text;
	float x, y;
	byte r, g, b, a;
};*/

//VARIABLE

//std::vector<text_box_t> textOnScreen;//NEW RECTANGUES ON PEDS

/*void entity_draw_info_add(std::vector<text_box_t>& textOnScreen, Entity entity, float mindist, float maxdist, std::string type, byte r, byte g, byte b, byte a)
{
	Vector3 v = ENTITY::GET_ENTITY_COORDS(entity, TRUE, FALSE);
	float x, y;
	if (GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(v.x, v.y, v.z, &x, &y))
	{
		// draw bounds
		if (x < 0.01 || y < 0.01 || x > 0.93 || y > 0.93)
			return;
		// get coords
		Vector3 plv = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE, FALSE);
		float dist = MISC::GET_DISTANCE_BETWEEN_COORDS(plv.x, plv.y, plv.z, v.x, v.y, v.z, TRUE);
		// draw text if entity isn't close to the player
		if (dist > mindist&& dist < maxdist)
		{
			// check if the text fits on screen
			bool bFitsOnscreen = true;
			for each (auto & iter in textOnScreen)
			{
				float textDist = sqrtf((iter.x - x) * (iter.x - x) + (iter.y - y) * (iter.y - y));
				if (textDist < 0.05)
				{
					bFitsOnscreen = false;
					break;
				}
			}
			// if text doesn't fit then skip draw
			if (!bFitsOnscreen) return;
			// add info to the vector
			int health = ENTITY::GET_ENTITY_HEALTH(entity);
			Hash model = ENTITY::GET_ENTITY_MODEL(entity);
			char text[256];
			sprintf_s(text, "\n\n DANGER! ", type.c_str(), "", "", "");
			textOnScreen.push_back({ text, x, y, r, g, b, a });
		}
	}
}*/

//PART OF BODY FOUND ALARM, NO FOUND IN WATER

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


//IF PLAYER OR CORPSE NEAR BUSH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*
			for (int k = 0; k < count; k++)
			{
				if (ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x1C77E342

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x6C0EB1C5

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x218F53BF

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x6A06CD6E

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x6C0EB1C5

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x1C77E342

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0xD0942505

					|| ENTITY::GET_ENTITY_MODEL(objects[k]) == 0x3CDCF6A2)
				{
					Vector3 v = ENTITY::GET_ENTITY_COORDS(objects[k], TRUE, FALSE);

					//PLAYER

					if (ENTITY::IS_ENTITY_IN_AREA(playerped, v.x - 3, v.y - 3, v.z - 3, v.x + 3, v.y + 3, v.z + 3, false, false, false))
					{
						bushcheckplayer = v;
					}

					//CORPSE

					if (PED::IS_PED_DEAD_OR_DYING(missionpeds[i], TRUE))
					{
						if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], v.x - 3, v.y - 3, v.z - 3, v.x + 3, v.y + 3, v.z + 3, false, false, false))
						{
							bushcheckped[i] = v;
						}
					}
				}
			}*/

			/*NOISE DETECTION

			if (TASK::IS_PED_RUNNING(playerped))
			{
				playercoordsrun = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE, TRUE);
				if (ENTITY::IS_ENTITY_IN_AREA(missionpeds[i], playercoordsrun.x - 2, playercoordsrun.y - 2, playercoordsrun.z - 2, playercoordsrun.x + 2, playercoordsrun.y + 2, playercoordsrun.z + 2, false, false, false))
				{
					TASK::TASK_COMBAT_PED(missionpeds[i], playerped, 0, 0);
				}
			}*/
