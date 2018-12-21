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
	std::vector<Area> country;
	PC pc;
	Area *pCurrentArea;
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
	void populateCountry();
	Object *masterObjectLookup(const std::string objectName);
	Location *masterLocationLookup(const std::string locationName);

public:
	Game();

	/* Mutators */

	/* Object */
	void createObject(std::string name, std::string description) { masterObjectList.push_back(new Object(name, description)); }
	void placeObject(std::string objectName, std::string locationName) { masterLocationLookup(locationName)->pushObject(masterObjectLookup(objectName)); }
	void placeObjects(std::vector<std::string> objectList, std::string locationName);

	/* Area */
	void createArea(std::vector<Location> locationMap);
};