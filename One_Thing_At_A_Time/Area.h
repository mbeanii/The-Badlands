#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Location.h"
#include "Object.h"

#define AREA_MAX_LOCATION_MAP_ROW_COL 2

class Area
{
private:
	Location locationMap[AREA_MAX_LOCATION_MAP_ROW_COL][AREA_MAX_LOCATION_MAP_ROW_COL];
	Location nullLocation;
	std::vector<Object *> *pMasterObjectList;

public:
	Area(std::vector<Object *> *rhs);
	Area();

	/* Accessors */
	bool checkNorth(Location *pCurrentLocation);
	bool checkEast(Location *pCurrentLocation);
	bool checkSouth(Location *pCurrentLocation);
	bool checkWest(Location *pCurrentLocation);

	Location *getNorth(Location *pCurrentLocation);
	Location *getEast(Location *pCurrentLocation);
	Location *getSouth(Location *pCurrentLocation);
	Location *getWest(Location *pCurrentLocation);

	Location *lookupLocationHere(std::string inputLocation);

	/* Accessors */
	Location getNullLocation() { return nullLocation; }

	/* Mutators */
	void addLocationToLocationMap(int row, int col, Location location) { locationMap[row][col] = location; };
	void createLocation(std::string name, std::string description, int row, int col);
	//void setpMasterObjectList(std::vector<Object *> *pList) { pMasterObjectList = pList; };

	void printLocationDescription(Location *pCurrentLocation) { std::cout << pCurrentLocation->getDescription() << std::endl; }
	void printSurroundings(Location *pCurrentLocation);
	void printObjectsHere(Location *pCurrentLocation);
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
