#include "Area.h"
#include "Map.h" // TODO: Remove me.

Area::Area(std::vector<Object *> *rhs)
{
	pMasterObjectList = rhs;
	for (int i = 0; i < AREA_MAX_LOCATION_MAP_ROW_COL; i++)
		for (int j = 0; j < AREA_MAX_LOCATION_MAP_ROW_COL; j++)
			locationMap[i][j] = nullLocation;
}

Area::Area()
{
	for (int i = 0; i < AREA_MAX_LOCATION_MAP_ROW_COL; i++)
		for (int j = 0; j < AREA_MAX_LOCATION_MAP_ROW_COL; j++)
			locationMap[i][j] = nullLocation;
}
/* Returns true if there exists a location to the north. Otherwise, returns false. */
inline bool Area::checkNorth(Location *pCurrentLocation)
{
	return (pCurrentLocation->getNextRow() < AREA_MAX_LOCATION_MAP_ROW_COL) ? !(locationMap[pCurrentLocation->getNextRow()][pCurrentLocation->getCol()].getName().empty()) : false;
}

inline bool Area::checkEast(Location *pCurrentLocation)
{
	return (pCurrentLocation->getNextCol() < AREA_MAX_LOCATION_MAP_ROW_COL) ? !(locationMap[pCurrentLocation->getRow()][pCurrentLocation->getNextCol()].getName().empty()) : false;
}

inline bool Area::checkSouth(Location *pCurrentLocation)
{
	return (pCurrentLocation->getPrevRow() >= 0) ? !(locationMap[pCurrentLocation->getPrevRow()][pCurrentLocation->getCol()].getName().empty()) : false;
}

inline bool Area::checkWest(Location *pCurrentLocation)
{
	return (pCurrentLocation->getPrevCol() >= 0) ? !(locationMap[pCurrentLocation->getRow()][pCurrentLocation->getPrevCol()].getName().empty()) : false;
}

inline Location *Area::getNorth(Location *pCurrentLocation)
{
	if (checkNorth(pCurrentLocation))
	{
		return &locationMap[pCurrentLocation->getNextRow()][pCurrentLocation->getCol()];
	}
	else
	{
		return &nullLocation;
	}
}

inline Location *Area::getEast(Location *pCurrentLocation)
{
	if (checkEast(pCurrentLocation))
	{
		return &locationMap[pCurrentLocation->getRow()][pCurrentLocation->getNextCol()];
	}
	else
	{
		return &nullLocation;
	}
}

inline Location *Area::getSouth(Location *pCurrentLocation)
{
	if (checkSouth(pCurrentLocation))
	{
		return &locationMap[pCurrentLocation->getPrevRow()][pCurrentLocation->getCol()];
	}
	else
	{
	return &nullLocation;
	}
}

inline Location *Area::getWest(Location *pCurrentLocation)
{
	if (checkWest(pCurrentLocation))
	{
		return &locationMap[pCurrentLocation->getRow()][pCurrentLocation->getPrevCol()];
	}
	else
	{
	return &nullLocation;
	}
}

void Area::printSurroundings(Location *pCurrentLocation)
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

void Area::printObjectsHere(Location *pCurrentLocation)
{
	if (pCurrentLocation->getObjectsHere().size() > 0)
		for (std::vector<Object *>::iterator it = pCurrentLocation->getObjectsHereBegin();
			it != pCurrentLocation->getObjectsHereEnd();
			++it)
			std::cout << "There is a " << (*it)->getName() << " here.\n";
}

Location *Area::lookupLocationHere(std::string locationName)
{
	for (int i = 0; i < AREA_MAX_LOCATION_MAP_ROW_COL; ++i)
	{
		for (int j = 0; j < AREA_MAX_LOCATION_MAP_ROW_COL; ++j)
		{
			if (locationMap[i][j].getName() == locationName)
			{
				return &(locationMap[i][j]);
			}
		}
	}
}

void Area::createLocation(std::string name, std::string description, int row, int col)
{
	// Define temporary Location
	Location newLocation;

	// Assign it the name
	newLocation.setName(name);

	// Assign it the description
	newLocation.setDescription(description);

	// Set the Location's row and column
	newLocation.setRow(row);
	newLocation.setCol(col);

	// Push it back onto pLocationMap using the row, col index
	addLocationToLocationMap(row, col, newLocation);
}

//StartArea::StartArea()
//{
//	farm.setName("moisture farm");
//	std::string tempString =
//		"This moisture farm is designed to harvest water "
//		"particulates in the air. It and the farms like it "
//		"are the most precious resource in the world.";
//	farm.setDescription(tempString);
//	tempString = "";
//	farm.setRow(FARM_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
//	farm.setCol(FARM_LOCATION_VALUE % STARTING_AREA_MAX_ROW);
//
//	tower.setName("water tower");
//	tempString = "This water tower is used by the farm for storage";
//	tower.setDescription(tempString);
//	tempString = "";
//	tower.setRow(TOWER_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
//	tower.setCol(TOWER_LOCATION_VALUE % STARTING_AREA_MAX_ROW);
//
//	waste.setName("barren waste");
//	tempString = "It is barren. And a waste. ";
//	waste.setDescription(tempString);
//	tempString = "";
//	waste.setRow(WASTE_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
//	waste.setCol(WASTE_LOCATION_VALUE % STARTING_AREA_MAX_ROW);
//
//	mountain.setName("mountain");
//	tempString =  "This is a mountain. It's probably impassable. So how are you here?";
//	mountain.setDescription(tempString);
//	tempString = "";
//	mountain.setRow(MOUNTAIN_LOCATION_VALUE / STARTING_AREA_MAX_ROW);
//	mountain.setCol(MOUNTAIN_LOCATION_VALUE % STARTING_AREA_MAX_ROW);;
//
//	// 2D Array for map
//	/*******************
//	*10WASTE*11MOUNTAIN*
//	********************
//	*00FARM *01TOWER   *
//	*******************/
//
//	addLocationToLocationMap(farm.getRow(), farm.getCol(), farm);
//	addLocationToLocationMap(tower.getRow(), tower.getCol(), tower);
//	addLocationToLocationMap(waste.getRow(), waste.getCol(), waste);
//	addLocationToLocationMap(mountain.getRow(), mountain.getCol(), mountain);
//}