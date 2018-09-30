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
* 
*********************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm> // for remove_if
#include <sstream>   // for stringstream

/* Locally defined header files */
#include "Character.h"
#include "Object.h"
#include "Location.h"
#include "Area.h"
#include "Game.h"

Game::Game()
{
	// INITIALIZE VARIABLES
	pCurrentArea = &startArea;
	pCurrentLocation = &startArea.farm;
	move = "";

	// DEFINE OBJECTS
	createObjects();

	// DEFINE CHARACTERS
	startingEquipment.push_back(&masterObjectList[WATER]);
	pc.setInventory(startingEquipment);

	// DEFINE LOCATIONS
	pCurrentArea->pMasterObjectList = &masterObjectList;

	// PLACE OBJECTS
	startArea.farm.objectsHere.push_back(&masterObjectList[SWORD]);
	startArea.mountain.objectsHere.push_back(&masterObjectList[CAT]);

	// INITIALIZE
	printIntro();
	printFullDescription();


	// MAIN LOOP

	while (1)
	{
		getMove();
		parseMove();
	}
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
	Object water;
	water.name = "water bottle";
	water.description = "Water is cool, refreshing, and necessary for life.";
	// The next two instructions always need to happen in succession, and in
	// the order specified by the OBJECTS enumerator. This allows indexing
	// into the master object list to retrieve an object from it by "name"
	water.id = WATER;
	masterObjectList.push_back(water);

	Object sword;
	sword.name = "sword";
	sword.description = "This crude blade is made from scraps of a worn-down building.";
	
	sword.id = SWORD;
	masterObjectList.push_back(sword);

	Object cat;
	cat.name = "cat";
	cat.description = "This scrawny feral feline looks ready for a row.";

	cat.id = CAT;
	masterObjectList.push_back(cat);
}

//EXECUTE MOVE
void Game::executeMove()
{
	if (move == "n" && pCurrentArea->checkNorth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getNorth(pCurrentLocation);
		printFullDescription();
	}
	else if (move == "e" && pCurrentArea->checkEast(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getEast(pCurrentLocation);
		printFullDescription();
	}
	else if (move == "s" && pCurrentArea->checkSouth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getSouth(pCurrentLocation);
		printFullDescription();
	}
	else if (move == "w" && pCurrentArea->checkWest(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getWest(pCurrentLocation);
		printFullDescription();
	}
}


void Game::executeMoveGet(std::string objectName)
{
	int objectNameID = -1; //initialize to invalid object ID number
	transform(objectName.begin(),objectName.end(),objectName.begin(),tolower);
	// this needs to be changed to handle any object (ie, by iterating through the master object list to find the object)
	// it also needs to check to make sure the object is actually there.
	// and it needs error messages for both of the above cases.

	//check to see if the object is there
	for(std::vector<Object *>::iterator it = pCurrentLocation->objectsHere.begin(); it != pCurrentLocation->objectsHere.end(); ++it)
		if ((*it)->name == objectName)
		{
			// remove it from the location
			(*it)->compareObjectName = objectName;	// to pass objectName into the lambda function on the next line
			objectNameID = (*it)->id;				// save off the object ID so we can add one to the masterObjectList
			pCurrentLocation->objectsHere.erase(remove_if(pCurrentLocation->objectsHere.begin(), pCurrentLocation->objectsHere.end(), [](Object *lhs) {return lhs->name == lhs->compareObjectName;}));
			// add it to inventory
			pc.pushInventory(&masterObjectList[objectNameID]);
			printFullDescription();
			return;
		}

		else	// The object isn't there.
		{
			std::cout << "You can't see a " << objectName << " here\n";
		}
}

void Game::getMove()
{
	std::getline(std::cin,move);
	std::cin.clear();
}

void Game::parseMove()
{
	if (move.length() == 1)
		executeMove();

	std::stringstream ss(move);
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