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

/* Locally defined header files */
#include "Character.h"
#include "Object.h"
#include "Location.h"
#include "Area.h"
#include "Game.h"
#include <assert.h> /* For assert */

Game::Game()
{
	// INITIALIZE VARIABLES
	pCurrentArea = &startArea;
	pCurrentLocation = &startArea.farm;
	command = "";

	// DEFINE OBJECTS
	createObjects();

	// DEFINE LOCATIONS
	pCurrentArea->setpMasterObjectList(&masterObjectList);

	// DEFINE CHARACTERS
	std::string objectName = "";
	try
	{
		// Store the object name as a variable for use by the exception handler.
		objectName = "water bottle";
		startingEquipment.push_back(masterObjectLookup(objectName));

		pc.setInventory(startingEquipment);
	}

	catch (const char* msg)
	{
		std::cerr << msg << objectName << std::endl;
	}

	// PLACE OBJECTS
	try
	{
		objectName = "sword";
		startArea.farm.pushObject(masterObjectLookup(objectName));

		objectName = "cat";
		startArea.mountain.pushObject(masterObjectLookup(objectName));
	}
	catch (const char* msg)
	{
		std::cerr << msg << objectName << std::endl;
	}

	// INITIALIZE
	printIntro();
	printFullDescription();


	// MAIN LOOP

	while (1)
	{
		uiGetMove();
		parseMove();
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

	/* Report that the object was not found in the list. */
	throw "Object not found: ";
}

void Game::printFullDescription()
{
	std::cout << std::endl;
	pCurrentLocation->printLocationName();
	pCurrentArea->printLocationDescription(pCurrentLocation);
	pc.printPCStatus();
	pCurrentArea->printSurroundings(pCurrentLocation);
	pCurrentArea->printObjectsHere(pCurrentLocation);
	pc.printInventory();
}

void Game::createObjects()
{
	createObject("water bottle",													/* name		   */
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
	Enum_Game_Error_Codes gameError = GAME_ERROR_NO_ERROR;
	Object *myObject = NULL;

	// Remove it from the location and add it to the pc's inventory.
	pc.pushInventory(pCurrentLocation->lookupObjectByName(objectName));
	pCurrentLocation->removeObject(objectName);
}


void Game::executeMoveGet(std::string objectName)
{
	transform(objectName.begin(),objectName.end(),objectName.begin(),tolower);

	if (pCurrentLocation->checkObjectIsHere(objectName))
		{
			pickUpObject(objectName);
			printFullDescription();
			return;
		}

		else	// The object isn't there.
		{
			std::cout << "You can't see a " << objectName << " here\n";
		}
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

int main(int argc, char** argv)
{
	Game game;
	return 0;
}