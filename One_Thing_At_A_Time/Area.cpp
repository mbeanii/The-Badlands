#include "Area.h"

// 2D Array for map
/*******************
*10WASTE*11MOUNTAIN*
********************
*00FARM *01TOWER   *
*******************/

/* Used to convert 1D enum to 2D array. */
#define STARTING_AREA_MAX_ROW 2

enum STARTING_AREA_LOCATIONS
{
	/* Row 0 */
	FARM_LOCATION_VALUE,
	TOWER_LOCATION_VALUE,

	/* Row 1 */
	WASTE_LOCATION_VALUE,
	MOUNTAIN_LOCATION_VALUE,

	MAX_LOCATION_VALUE
};

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

inline bool Area::checkNorth(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row + 1 <= MAP_GRID_MAX_SIZE);
}

inline bool Area::checkEast(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1] != '\0') && (pCurrentLocation->col + 1 <= MAP_GRID_MAX_SIZE);
}

inline bool Area::checkSouth(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col] != '\0') && (pCurrentLocation->row - 1 >= 0);
}

inline bool Area::checkWest(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->row][pCurrentLocation->col - 1] != '\0') && (pCurrentLocation->col - 1 >= 0);
}

inline Location * Area::getNorth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row + 1][pCurrentLocation->col];
}

inline Location * Area::getEast(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row][pCurrentLocation->col + 1];
}

inline Location * Area::getSouth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->row - 1][pCurrentLocation->col];
}

inline Location * Area::getWest(Location * pCurrentLocation)
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
		farm.row = (FARM_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		farm.col = (FARM_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		tower.name = "water tower";
		tower.description = "This water tower is used by the farm for storage";
		tower.row = (TOWER_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		tower.col = (TOWER_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		waste.name = "barren waste";
		waste.description = "It is barren. And a waste. ";
		waste.row = (WASTE_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		waste.col = (WASTE_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		mountain.name = "mountain";
		mountain.description = "This is a mountain. It's probably impassable. So how are you here?";
		mountain.row = (MOUNTAIN_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		mountain.col = (MOUNTAIN_LOCATION_VALUE % STARTING_AREA_MAX_ROW);;

		// 2D Array for map
		/*******************
		*10WASTE*11MOUNTAIN*
		********************
		*00FARM *01TOWER   *
		*******************/

		addpLocationTopLocationMap(farm.row, farm.col, &farm);
		addpLocationTopLocationMap(tower.row, tower.col, &tower);
		addpLocationTopLocationMap(waste.row, waste.col, &waste);
		addpLocationTopLocationMap(mountain.row, mountain.col, &mountain);
	}