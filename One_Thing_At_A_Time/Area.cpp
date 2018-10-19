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
	return (pLocationMap[pCurrentLocation->getNextRow()][pCurrentLocation->getCol()] != '\0') && (pCurrentLocation->getNextRow() <= MAP_GRID_MAX_SIZE);
}

inline bool Area::checkEast(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->getRow()][pCurrentLocation->getNextCol()] != '\0') && (pCurrentLocation->getNextCol() <= MAP_GRID_MAX_SIZE);
}

inline bool Area::checkSouth(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->getPrevRow()][pCurrentLocation->getCol()] != '\0') && (pCurrentLocation->getPrevRow() >= 0);
}

inline bool Area::checkWest(Location * pCurrentLocation)
{
	return (pLocationMap[pCurrentLocation->getRow()][pCurrentLocation->getPrevCol()] != '\0') && (pCurrentLocation->getPrevCol() >= 0);
}

inline Location * Area::getNorth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->getNextRow()][pCurrentLocation->getCol()];
}

inline Location * Area::getEast(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->getRow()][pCurrentLocation->getNextCol()];
}

inline Location * Area::getSouth(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->getPrevRow()][pCurrentLocation->getCol()];
}

inline Location * Area::getWest(Location * pCurrentLocation)
{
	return pLocationMap[pCurrentLocation->getRow()][pCurrentLocation->getPrevCol()];
}

void Area::printSurroundings(Location * pCurrentLocation)
{
	if (checkNorth(pCurrentLocation))
		std::cout << "To the North lies a " << getNorth(pCurrentLocation)->getName()
		<< "." << std::endl;
	if (checkEast(pCurrentLocation))
		std::cout << "To the East lies a " << getEast(pCurrentLocation)->getName()
		<< "." << std::endl;
	if (checkSouth(pCurrentLocation))
		std::cout << "To the South lies a " << getSouth(pCurrentLocation)->getName()
		<< "." << std::endl;
	if (checkWest(pCurrentLocation))
		std::cout << "To the West lies a " << getWest(pCurrentLocation)->getName()
		<< "." << std::endl;
}

void Area::printObjectsHere(Location * pCurrentLocation)
{
	if (pCurrentLocation->getObjectsHere().size() > 0)
		for (std::vector<Object *>::iterator it = pCurrentLocation->getObjectsHereBegin();
			it != pCurrentLocation->getObjectsHereEnd();
			++it)
			std::cout << "There is a " << (*it)->name << " here.\n";
}

StartArea::StartArea()
	{
		farm.setName("moisture farm");
		std::string tempString =
			"This moisture farm is designed to harvest water "
			"particulates in the air. It and the farms like it "
			"are the most precious resource in the world.";
		farm.setDescription(tempString);
		tempString = "";
		farm.setRow(FARM_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		farm.setCol(FARM_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		tower.setName("water tower");
		tempString = "This water tower is used by the farm for storage";
		tower.setDescription(tempString);
		tempString = "";
		tower.setRow(TOWER_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		tower.setCol(TOWER_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		waste.setName("barren waste");
		tempString = "It is barren. And a waste. ";
		waste.setDescription(tempString);
		tempString = "";
		waste.setRow(WASTE_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		waste.setCol(WASTE_LOCATION_VALUE % STARTING_AREA_MAX_ROW);

		mountain.setName("mountain");
		tempString =  "This is a mountain. It's probably impassable. So how are you here?";
		mountain.setDescription(tempString);
		tempString = "";
		mountain.setRow(MOUNTAIN_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
		mountain.setCol(MOUNTAIN_LOCATION_VALUE % STARTING_AREA_MAX_ROW);;

		// 2D Array for map
		/*******************
		*10WASTE*11MOUNTAIN*
		********************
		*00FARM *01TOWER   *
		*******************/

		addpLocationTopLocationMap(farm.getRow(), farm.getCol(), &farm);
		addpLocationTopLocationMap(tower.getRow(), tower.getCol(), &tower);
		addpLocationTopLocationMap(waste.getRow(), waste.getCol(), &waste);
		addpLocationTopLocationMap(mountain.getRow(), mountain.getCol(), &mountain);
	}