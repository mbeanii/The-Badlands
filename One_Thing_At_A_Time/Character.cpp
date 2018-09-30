#include "Character.h"

#include <iostream>
#include <vector>

void PC::printInventory()
{
	std::cout << "You have a ";
	for (std::vector<Object*>::iterator it = inventory.begin(), end = inventory.end(); it != end; ++it) {
		std::cout << (*it)->name;
		if (*it != inventory.back())
		{
			if (*(++it) == inventory.back()) // Temporarily increment it to check the next item.
			{
				std::cout << " and a ";
				--it;						 // Reverse temporary increment.
			}
			else
			{
				--it;						 // Reverse temporary increment.
				std::cout << ", ";
			}
		}
	}
	std::cout << "." << std::endl;
}