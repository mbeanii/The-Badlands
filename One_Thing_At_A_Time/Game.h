#pragma once

#include <string>
#include <vector>

#include "Area.h"
#include "Location.h"
#include "Character.h"

/* Enums */

enum Enum_Game_Error_Codes
{
	GAME_ERROR_NO_ERROR         = 0,
	GAME_ERROR_OBJECT_NOT_FOUND = 1,		/* lookupObjectByName */
	GAME_ERROR_MAX_ERROR_CODE   = 2,
};

/* Classes */

class Game
{
private:
	std::vector<Object *> masterObjectList;
	std::vector<Object *> startingEquipment;
	PC pc;
	StartArea startArea;
	Area * pCurrentArea;
	Location *pCurrentLocation;
	std::string command = "";

	void createObjects();
	void printFullDescription();
	void executeMove();
	void executeMoveGet(std::string objectName);
	void uiGetMove();
	void parseMove();
	void printIntro();
	void pickUpObject(std::string objectName);
	Object *masterObjectLookup(const std::string objectName);

public:
	Game();
	void Game::createObject(std::string name, std::string description) { masterObjectList.push_back(new Object(name, description)); }
};