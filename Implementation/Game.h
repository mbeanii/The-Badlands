#pragma once

#include <string>
#include <vector>

#include "Area.h"
#include "Location.h"
#include "Game_Character.h"

/* Classes */

class Game
{
private:
	std::vector<Object *> masterObjectList;
	std::vector<Object *> startingEquipment;
	std::vector<Area> country;
	std::vector<Character *> masterCharacterList;
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
	Character *masterCharacterLookup(const std::string characterName);

	// Takes an input string with comma seperated names of object strings and returns a vector of object strings
	std::vector<std::string> parseObjectString(std::string inputString);

public:
	Game();

	/* Mutators */

	/* Object */
	void createObject(std::string inputName, std::string inputDescription, std::vector<std::string> inputActionList) { masterObjectList.push_back(new Object(inputName, inputDescription, inputActionList)); }
	void placeObject(std::string objectName, std::string locationName) { masterLocationLookup(locationName)->pushObject(masterObjectLookup(objectName)); }
	void placeObjects(std::string inputString, std::string locationName);
	void populateInventory(std::string inputString, std::string inputCharacter);
	void giveObject(std::string inputObject, std::string character);


	/* Character */
	void createCharacter(std::string inputName, Status_Type inputStatus) { masterCharacterList.push_back(new Character(inputName, inputStatus)); }

	/* Area */
	void createArea(std::vector<Location> locationMap);
};