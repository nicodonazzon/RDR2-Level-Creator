#pragma once
#include "script.h"
const Hash BLIP_STYLE_ENEMY = 0x318C617C;
const Hash BLIP_TYPE_BOUNTY_TARGET = 0x38CDE89D;
const Hash BLIP_SPRITE_BOUNTY_TARGET = 0x5846C31D;
Object createProp(char* model, Vector3 position, float heading = 0, bool isStatic = false, bool isVisible = true);

Object createProp(char* model, Vector3 position, float heading, bool isStatic, bool isVisible)
{
	Hash modelHash = MISC::GET_HASH_KEY(model);

	if (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		STREAMING::REQUEST_MODEL(modelHash, false);
	}

	while (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		WAIT(0);
	}

	Object prop = OBJECT::CREATE_OBJECT(modelHash, position.x, position.y, position.z, false, false, !isStatic, 0, 0);
	ENTITY::SET_ENTITY_HEADING(prop, heading);
	ENTITY::FREEZE_ENTITY_POSITION(prop, isStatic);
	ENTITY::SET_ENTITY_VISIBLE(prop, isVisible);

	return prop;
}


Blip createBlip(Vector3 pos, Hash blipType, Hash blipSprite)
{
	Blip blip;
	Object dummyProp = createProp("p_shotGlass01x", pos, true, false);

	blip = MAP::_BLIP_ADD_FOR_ENTITY(blipType, dummyProp); // Add blip for dummy prop
	if (blipSprite != 0)
	{
		MAP::SET_BLIP_SPRITE(blip, blipSprite, false);
	}

	return blip;
}

Blip createBlip(Entity entity, Hash blipType, Hash blipSprite)
{
	Blip blip = MAP::_BLIP_ADD_FOR_ENTITY(blipType, entity);

	if (blipSprite != 0)
	{
		MAP::SET_BLIP_SPRITE(blip, blipSprite, false);
	}

	return blip;
}

Blip createBlip(Vector3 source, float radius, Hash blipType, Hash blipSprite)
{
	Blip blip = MAP::_BLIP_ADD_FOR_RADIUS(blipType, source.x, source.y, source.z, radius); // add blip for area

	if (blipSprite != 0)
	{
		MAP::SET_BLIP_SPRITE(blip, blipSprite, false);
	}

	return blip;
}

void setBlipLabel(Blip blip, const char* label)
{
	MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(blip, /*(Any*)*/MISC::_CREATE_VAR_STRING2(10, "LITERAL_STRING", label)); // _SET_BLIP_NAME_FROM_PLAYER_STRING
}

void deleteBlipSafe(Blip* blip)
{
	if (MAP::DOES_BLIP_EXIST(*blip))
	{
		MAP::REMOVE_BLIP(blip);
	}
}
