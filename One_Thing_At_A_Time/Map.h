#pragma once

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