#pragma once

#include <string>
#include <vector>

#include "Area.h"
#include "Location.h"
#include "Character.h"


class Game
{
public:
	std::vector<Object> masterObjectList;
	std::vector<Object *> startingEquipment;
	PC pc;
	StartArea startArea;
	Area * pCurrentArea;
	Location *pCurrentLocation;
	std::string move = "";

	Game();
	void createObjects();
	void printFullDescription();
	void executeMove();
	void executeMoveGet(std::string objectName);
	void getMove();
	void parseMove();
	void printIntro();
};