#include "Area.h"

Area::Area(std::vector<Object> *rhs)
{
	pMasterObjectList = rhs;
	for (int i = 0; i < MAP_GRID_MAX_SIZE; i++)
		for (int j = 0; j < MAP_GRID_MAX_SIZE; j++)
			pLocationMap[i][j] = '\0';
}

Area::Area()
{
	for (int i = 0; i < MAP_GRID_MAX_SIZE; i++)
		for (int j = 0; j < MAP_GRID_MAX_SIZE; j++)
			pLocationMap[i][j] = '\0';
}

bool Area::checkNorth(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row + 1 <= MAP_GRID_MAX_SIZE);
}

bool Area::checkEast(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1] != '\0') && (pCurrentLocation->col + 1 <= MAP_GRID_MAX_SIZE);
}

bool Area::checkSouth(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row - 1 >= 0);
}

bool Area::checkWest(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col - 1] != '\0') && (pCurrentLocation->col - 1 >= 0);
}

Location * Area::getNorth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col];
}

Location * Area::getEast(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1];
}

Location * Area::getSouth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col];
}

Location * Area::getWest(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row][pCurrentLocation->col - 1];
}

void Area::printSurroundings(Location * pCurrentLocation)
{
	if (checkNorth(pCurrentLocation))
		std::cout << "To the North lies a " << getNorth(pCurrentLocation)->name
		<< "." << std::endl;
	if (checkEast(pCurrentLocation))
		std::cout << "To the East lies a " << getEast(pCurrentLocation)->name
		<< "." << std::endl;
	if (checkSouth(pCurrentLocation))
		std::cout << "To the South lies a " << getSouth(pCurrentLocation)->name
		<< "." << std::endl;
	if (checkWest(pCurrentLocation))
		std::cout << "To the West lies a " << getWest(pCurrentLocation)->name
		<< "." << std::endl;
}

void Area::printObjectsHere(Location * pCurrentLocation)
{
	if (pCurrentLocation->objectsHere.size() > 0)
		for (std::vector<Object *>::iterator it = pCurrentLocation->objectsHere.begin();
			it != pCurrentLocation->objectsHere.end();
			++it)
			std::cout << "There is a " << (*it)->name << " here.\n";
}

StartArea::StartArea()
	{
		farm.name = "moisture farm";
		farm.description =
			"This moisture farm is designed to harvest water "
			"particulates in the air. It and the farms like it "
			"are the most precious resource in the world.";
		farm.row = 0;
		farm.col = 0;

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
		*00FARM *01TOWER   *
		*******************/
		pLocationMap[0][0] = &farm;
		pLocationMap[0][1] = &tower;
		pLocationMap[1][0] = &waste;
		pLocationMap[1][1] = &mountain;

	}