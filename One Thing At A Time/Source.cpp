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


// 2D Array for map
/*******************
* WASTE * MOUNTAIN *
********************
* FARM  *WATERTOWER*
*******************/

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#define MAP_GRID_MAX_SIZE 4
enum ALL_OBJECTS { WATER, SWORD };

using namespace std;

class Object;
class Character;
class PC;
class Location;
class Area;
class StartArea;


class Object
{
public:
	string name;
	string description;
	int id;
};

class Character
{
public:
	string status;
	vector<Object*> inventory;
};

class PC : public Character
{
public:
	PC(vector<Object*> startingEquipment)
	{
		status = "dirty";
		inventory = startingEquipment;
	}

	void printPCStatus() { cout << "You are " << status << "." << endl; }
	void printInventory()
	{
		cout << "You have a ";
		for (vector<Object*>::iterator it = inventory.begin(), end = inventory.end(); it != end; ++it) {
			cout << (*it)->name;
			if (*it != inventory.back())
			{
				if (*(++it) == inventory.back())
				{
					cout << " and ";
					--it;
				}
				else
					cout << ", ";
			}
		}
		cout << "." << endl;
	}
};

class Location
{
public:
	string name;
	string description;
	short row;
	short col;
	vector<Object *> objectsHere;

	void printLocationName() { cout << "You are at the " << name << "." << endl; }
};

class Area
{
 public:

	 Location *pLocationMap[MAP_GRID_MAX_SIZE][MAP_GRID_MAX_SIZE];
	 vector<Object> *pMasterObjectList;

	 Area(vector<Object> *rhs)
	 {
		 pMasterObjectList = rhs;
		 for (int i = 0; i < MAP_GRID_MAX_SIZE; i++)
			 for (int j = 0; j < MAP_GRID_MAX_SIZE; j++)
				 pLocationMap[i][j] = '\0';
	}

	 Area()
	 {
		 for (int i = 0; i < MAP_GRID_MAX_SIZE; i++)
			 for (int j = 0; j < MAP_GRID_MAX_SIZE; j++)
				 pLocationMap[i][j] = '\0';
	 }

	bool checkNorth(Location * pCurrentLocation)
	{return (pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row + 1 <= MAP_GRID_MAX_SIZE);}

	bool checkEast(Location * pCurrentLocation)
	{return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1] != '\0') && (pCurrentLocation->col + 1 <= MAP_GRID_MAX_SIZE);}

	bool checkSouth(Location * pCurrentLocation)
	{return (pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row - 1 >= 0);}

	bool checkWest(Location * pCurrentLocation)
	{return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col - 1] != '\0') && (pCurrentLocation->col - 1 >= 0);}

	Location * getNorth(Location * pCurrentLocation)
	{return pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col];}

	Location * getEast(Location * pCurrentLocation)
	{return pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1];}

	Location * getSouth(Location * pCurrentLocation)
	{return pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col];}

	Location * getWest(Location * pCurrentLocation)
	{return pLocationMap[pCurrentLocation->row][pCurrentLocation->col - 1];}

	void printLocationDescription(Location * pCurrentLocation){cout << pCurrentLocation->description << endl;}

	void printSurroundings(Location * pCurrentLocation);

	void printObjectsHere(Location * pCurrentLocation);
};

void Area::printSurroundings(Location * pCurrentLocation)
{
	if (checkNorth(pCurrentLocation))
		cout << "To the North lies a " << getNorth(pCurrentLocation)->name
		<< "." << endl;
	if (checkEast(pCurrentLocation))
		cout << "To the East lies a " << getEast(pCurrentLocation)->name
		<< "." << endl;
	if (checkSouth(pCurrentLocation))
		cout << "To the South lies a " << getSouth(pCurrentLocation)->name
		<< "." << endl;
	if (checkWest(pCurrentLocation))
		cout << "To the West lies a " << getWest(pCurrentLocation)->name
		<< "." << endl;
}

void Area::printObjectsHere(Location * pCurrentLocation)
{
	if (pCurrentLocation->objectsHere.size() > 0)
		for (vector<Object *>::iterator it = pCurrentLocation->objectsHere.begin();
			it != pCurrentLocation->objectsHere.end();
			++it)
			cout << "There is a " << (*it)->name << " here.\n";

}

class StartArea : public Area
{
public:
	/*******************
	*10WASTE*11MOUNTAIN*
	********************
	*00FARM *01 TOWER  *
	*******************/
	Location farm;
	Location tower;
	Location waste;
	Location mountain;

	StartArea(vector<Object> *rhs)
	{
		pMasterObjectList = rhs;

		farm.name = "moisture farm";
		farm.description =
			"This moisture farm is designed to harvest water "
			"particulates in the air. It and the farms like it "
			"are the most precious resource in the world.";
		farm.row = 0;
		farm.col = 0;
		farm.objectsHere.push_back(&(*pMasterObjectList)[SWORD]);

		tower.name = "water tower";
		tower.description = "This water tower is used by the farm for storage";
		tower.row = 0;
		tower.col = 1;

		waste.name = "barren waste";
		waste.description = "It is barren. And a waste. ";
		waste.row = 1;
		waste.col = 0;

		mountain.name = "mountain";
		mountain.description = "This is a mountain.";
		mountain.row = 1;
		mountain.col = 1;

		// 2D Array for map
		/*******************
		*10WASTE*11MOUNTAIN*
		********************
		*00FARM *01 TOWER  *
		*******************/
		pLocationMap[0][0] = &farm;
		pLocationMap[0][1] = &tower;
		pLocationMap[1][0] = &waste;
		pLocationMap[1][1] = &mountain;

	}
};

class Game
{
public:
	vector<Object> masterObjectList;
	vector<Object *> startingEquipment;
	PC pc;
	PC *ppc = &pc;
	StartArea startArea;
	Area * pCurrentArea = &startArea;
	Location *pCurrentLocation = &startArea.farm;
	string move = "";
	string *pMove = &move;

	Game() : pc(startingEquipment), startArea(&masterObjectList)
	{
		Area * pCurrentArea = &startArea;
		Location *pCurrentLocation = &startArea.farm;
		string move = "";
		string *pMove = &move;
	}

};

void printFullDescription(
	PC * ppc,
	Area * pCurrentArea,
	Location * pCurrentLocation)

{
	pCurrentLocation->printLocationName();
	ppc->printPCStatus();
	pCurrentArea->printSurroundings(pCurrentLocation);
	pCurrentArea->printLocationDescription(pCurrentLocation);
	pCurrentArea->printObjectsHere(pCurrentLocation);
	ppc->printInventory();
}

void createObjects(vector<Object>* masterObjectList)
{
	Object water;
	water.name = "water bottle";
	water.description = "Water is cool, refreshing, and necessary for life.";
	// The next two instructions always need to happen in succession, and in
	// the order specified by the ALL_OBJECTS enumerator. This allows indexing
	// into the master object list to retrieve an object from it by "name"
	water.id = WATER;
	masterObjectList->push_back(water);

	Object sword;
	sword.name = "crude sword";
	sword.description = "This crude blade is made from scraps of a worn-down building.";
	
	sword.id = SWORD;
	masterObjectList->push_back(sword);
}

//EXECUTE MOVE
void executeMove(string *pMove, Area *pCurrentArea, Location *pCurrentLocation, PC *ppc)
{
	if (*pMove == "n" && pCurrentArea->checkNorth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getNorth(pCurrentLocation);
		printFullDescription(ppc, pCurrentArea, pCurrentLocation);
	}
	else if (*pMove == "e" && pCurrentArea->checkEast(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getEast(pCurrentLocation);
		printFullDescription(ppc, pCurrentArea, pCurrentLocation);
	}
	else if (*pMove == "s" && pCurrentArea->checkSouth(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getSouth(pCurrentLocation);
		printFullDescription(ppc, pCurrentArea, pCurrentLocation);
	}
	else if (*pMove == "w" && pCurrentArea->checkWest(pCurrentLocation))
	{
		pCurrentLocation = pCurrentArea->getWest(pCurrentLocation);
		printFullDescription(ppc, pCurrentArea, pCurrentLocation);
	}
}

void getMove(string *pMove)
{
	cin >> *pMove;
}

void parseMove(string *pMove)
{
}

void printIntro()
{
	cout << "Welcome to hell." << endl << endl;
}



int main(int argc, char** argv)
{

	// DEFINE OBJECTS
	vector<Object> masterObjectList;
	createObjects(&masterObjectList);

	// DEFINE CHARACTERS
	vector<Object *> startingEquipment;
	startingEquipment.push_back(&masterObjectList[WATER]);
	PC pc(startingEquipment);
	PC *ppc = &pc;

	// DEFINE LOCATIONS
	StartArea startArea(&masterObjectList);
	Area * pCurrentArea = &startArea;
	Location *pCurrentLocation = &startArea.farm;

	// INITIALIZE
	string move = "";
	string *pMove = &move;
	printIntro();
	printFullDescription(ppc, pCurrentArea, pCurrentLocation);


	// MAIN LOOP

	while (1)
	{
		getMove(pMove);
		parseMove(pMove);
		executeMove(pMove, pCurrentArea, pCurrentLocation, ppc);
	}

	return 0;
}