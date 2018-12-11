#pragma once

#include <string>
#include <vector>

#include "Area.h"
#include "Location.h"
#include "Character.h"

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