/********************************************************
* The Badlands
*	Story by Frank Alvarado
*	Code by Marcus Bean
*
*
*	The world is in chaos. International wars have wiped
* out the majority of the population. City states have
* risen from the ashes of society and most are led by
* cruel tyrants. One in particular prides itself on it's
* mass amounts of oil they frack from the earth. Weapons
* of any sort are outlawed unless you serve the local
* regime. Firearms are almost nonexistent as the rulers of
* most city states destroyed them to prevent uprisings.
* Their footsoldiers are primarily armed with crude looking
* axes, swords and clubs made from scraps of worn down
* buildings. The Elite Guard is armed with weapons from the
* Old World from Tyler's personal cache. Slavery is rampant,
* especially in the oil fields. Moisture farms designed to
* process water particulates in the air are the most precious
* resource in the world. There is a threat of war looming
* on the horizon. It is said that one of the city-states has
* developed a weapon capable of wiping out all life in an
* area without harming structures or other resources.
*********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>   // for stringstream
#include <assert.h> /* For assert */

/* Locally defined header files */
#include "Character.h"
#include "Object.h"
#include "Location.h"
#include "Area.h"
#include "Game.h"
#include "Map.h"

Game::Game()
{
	// POPULATE COUNTRY
	populateCountry();

	// INITIALIZE VARIABLES
	pCurrentArea = &country[0];
	pCurrentLocation = country[0].lookupLocationHere("moisture farm");
	command = "";

	// DEFINE OBJECTS
	createObjects();

	// DEFINE LOCATIONS
//	pCurrentArea->setpMasterObjectList(&masterObjectList);

	// DEFINE CHARACTERS
	try
	{
		masterCharacterList.push_back(&pc);
		// startingEquipment.push_back(masterObjectLookup("water"));
		// pc.setInventory(startingEquipment);
		populateInventory("water, sword", "pc");

		createCharacter("Bob", STATUS_HUNGRY); // TODO: Place Bob somewhere. Print that Bob is there. Eventually fight Bob.

	// PLACE OBJECTS
		//startArea.farm.pushObject(masterObjectLookup("sword")); // TODO change object push to placeObject("sword", "farm");
		placeObject("sword", "moisture farm");

		//startArea.mountain.pushObject(masterObjectLookup("cat")); // TODO change object push
		placeObject("cat", "mountain");

		placeObjects("cat, water, sword", "water tower");
	}
	catch (char *msg)
	{
		std::cerr << msg << std::endl;
	}

	// INITIALIZE
	printIntro();
	printFullDescription();


	// MAIN LOOP

	while (1)
	{
		try
		{
			uiGetMove();
			parseMove();
		}
		catch (char *msg)
		{
			std::cerr << msg << std::endl;
		}
	}
}

Object *Game::masterObjectLookup(const std::string objectName)
{
	for (std::vector<Object *>::iterator it = masterObjectList.begin(); it != masterObjectList.end(); ++it)
	{
		if ((*it)->getName() == objectName)
		{
			return *it;
		}
	}

	/* If the object was not found in the list. */
	throw ("Game::masterObjectLookup Object not found.");
}

void Game::printFullDescription()
{
	std::cout << std::endl;
	pCurrentLocation->printLocationName();
	pCurrentArea->printLocationDescription(pCurrentLocation);
	masterCharacterLookup("pc")->printStatus();
	pCurrentArea->printSurroundings(pCurrentLocation);
	pCurrentArea->printObjectsHere(pCurrentLocation);
	masterCharacterLookup("pc")->printInventory();
}

void Game::createObjects()
{
	createObject("water",															/* name		   */
				"Water is cool, refreshing, and necessary for life.");				/* description */

	createObject("sword",															/* name		   */
				 "This crude blade is made from scraps of a worn-down building.");	/* description */

	createObject("cat",																/* name		   */
			   "This scrawny feral feline looks ready for a row.");					/* description */
}

//EXECUTE MOVE
void Game::executeMove()
{
	if (command == "n" && pCurrentArea->checkNorth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getNorth(pCurrentLocation);
		printFullDescription();
	}
	else if (command == "e" && pCurrentArea->checkEast(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getEast(pCurrentLocation);
		printFullDescription();
	}
	else if (command == "s" && pCurrentArea->checkSouth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getSouth(pCurrentLocation);
		printFullDescription();
	}
	else if (command == "w" && pCurrentArea->checkWest(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getWest(pCurrentLocation);
		printFullDescription();
	}
}

void Game::pickUpObject(std::string objectName)
{
	// Remove it from the location and add it to the pc's inventory.
	giveObject(pCurrentLocation->lookupObjectHere(objectName)->getName(), "pc");
	pCurrentLocation->removeObject(objectName);
}


void Game::executeMoveGet(std::string objectName)
{
	transform(objectName.begin(),objectName.end(),objectName.begin(),tolower);


	pickUpObject(objectName);
	printFullDescription();
	return;
}

void Game::uiGetMove()
{
	std::getline(std::cin,command);
	std::cin.clear();
}

void Game::parseMove()
{
	if (command.length() == 1)
		executeMove();

	std::stringstream ss(command);
	std::string moveFirstWord = "";
	std::string moveSecondWord = "";
	std::string moveThirdWord = "";
	std::string moveFourthWord = "";

	ss >> moveFirstWord;
	ss >> moveSecondWord;
	ss >> moveThirdWord;
	ss >> moveFourthWord;

	if (moveFirstWord == "get")
		executeMoveGet(moveSecondWord);
}

void Game::printIntro()
{
	std::cout << "Welcome to hell." << std::endl << std::endl;
}

void Game::placeObjects(std::string inputString, std::string locationName)
{
	std::vector<std::string> objectList = parseObjectString(inputString);
	for (std::vector<std::string>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		placeObject(*it, locationName);
	}
}

Location *Game::masterLocationLookup(const std::string locationName)
{
	Location *pTempLocation;
	for (std::vector<Area>::iterator it = country.begin(); it != country.end(); ++it)
	{
			pTempLocation = (*it).lookupLocationHere(locationName);
			if (pTempLocation != &((*it).getNullLocation()))
			{
				return pTempLocation;
			}
	}

	/* If the location was not found in the list. */
	throw ("Game::masterLocationLookup: Location not found.");
}

Character *Game::masterCharacterLookup(const std::string characterName)
{
	for (std::vector<Character *>::iterator it = masterCharacterList.begin(); it != masterCharacterList.end(); ++it)
	{
		if ((*it)->getName() == characterName)
		{
			return *it;
		}
	}

	/* If the location was not found in the list. */
	throw ("Game::masterLocationLookup: Location not found.");
}

void Game::populateInventory(std::string inputString, std::string inputCharacter)
{
	std::vector<std::string> objectList = parseObjectString(inputString);
	for (std::vector<std::string>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		giveObject(*it, inputCharacter);
	}
}

void Game::giveObject(std::string inputObject, std::string inputCharacter)
{
	Character *pCharacter = masterCharacterLookup(inputCharacter);
	pCharacter->pushInventory(masterObjectLookup(inputObject));
}

void Game::populateCountry()
{
	Area startArea;
	/* Where "startArea" is an "Area" -- get rid of all this inheritance nonsense */
	startArea.createLocation("moisture farm",					  /* name		  */
		"This moisture farm is designed to harvest water particulates in the air. \
It and the farms like it are the most precious resource in the world.",			  
																  /* description  */
		FARM_LOCATION_VALUE / STARTING_AREA_MAX_ROW,              /* row          */
		FARM_LOCATION_VALUE % STARTING_AREA_MAX_ROW);             /* col          */

	startArea.createLocation("water tower",					      /* name		  */
		"This water tower is used by the farm for storage",	      /* description  */
		TOWER_LOCATION_VALUE / STARTING_AREA_MAX_ROW,             /* row          */
		TOWER_LOCATION_VALUE % STARTING_AREA_MAX_ROW);            /* col          */

	startArea.createLocation("barren waste",					  /* name		  */
		"It is barren. And a waste.",	                          /* description  */
		WASTE_LOCATION_VALUE / STARTING_AREA_MAX_ROW,             /* row          */
		WASTE_LOCATION_VALUE % STARTING_AREA_MAX_ROW);            /* col          */

	startArea.createLocation("mountain",					      /* name		  */
		"This mountain is probably impassable. So how are you here?",	                                  /* description  */
		MOUNTAIN_LOCATION_VALUE / STARTING_AREA_MAX_ROW,          /* row          */
		MOUNTAIN_LOCATION_VALUE % STARTING_AREA_MAX_ROW);         /* col          */

	country.push_back(startArea);
	return;
}

void Game::createArea(std::vector<Location> locationMap)
{
	Area newArea;
	int i = 0;
	for (std::vector<Location>::iterator it = locationMap.begin(); it != locationMap.end(); ++it)
	{
		newArea.addLocationToLocationMap((it->getRow()),(it->getCol()), *it);
		i++;
	}
	country.push_back(newArea);
}

std::vector<std::string> Game::parseObjectString(std::string inputString)
{
	std::string tempString("");
	std::vector<std::string> returnStringVector;
	for (int i = 0; i != inputString.length(); i++)
	{
		if (inputString[i] != ',')
		{
			tempString += inputString[i];
		}
		else
		{
			returnStringVector.push_back(tempString);
			tempString = "";

			// Skip the space
			i++;
			if (inputString[i] != ' ')
			{
				i--;
			}
		}
	}
	returnStringVector.push_back(tempString);
	return returnStringVector;
}

int main(int argc, char** argv)
{
	Game game;

	return 0;
}