#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Location.h"
#include "Object.h"

#define MAP_GRID_MAX_SIZE 4

class Area
{
private:
	Location *pLocationMap[MAP_GRID_MAX_SIZE][MAP_GRID_MAX_SIZE];
	std::vector<Object *> *pMasterObjectList;

public:
	Area(std::vector<Object *> *rhs);
	Area();

	/* Accessors */
	bool checkNorth(Location * pCurrentLocation);
	bool checkEast(Location * pCurrentLocation);
	bool checkSouth(Location * pCurrentLocation);
	bool checkWest(Location * pCurrentLocation);

	Location * getNorth(Location * pCurrentLocation);
	Location * getEast(Location * pCurrentLocation);
	Location * getSouth(Location * pCurrentLocation);
	Location * getWest(Location * pCurrentLocation);

	/* Mutators */
	void addpLocationTopLocationMap(int row, int col, Location * pLocation) { pLocationMap[row][col] = pLocation; };
	void setpMasterObjectList(std::vector<Object *> *pList) { pMasterObjectList = pList; };

	void printLocationDescription(Location * pCurrentLocation) { std::cout << pCurrentLocation->getDescription() << std::endl; }
	void printSurroundings(Location * pCurrentLocation);
	void printObjectsHere(Location * pCurrentLocation);
};


class StartArea : public Area
{

public:

	// 2D Array for map
	/*******************
	* WASTE * MOUNTAIN *
	********************
	* FARM  *WATERTOWER*
	*******************/

	Location farm;
	Location tower;
	Location waste;
	Location mountain;

	StartArea();
};