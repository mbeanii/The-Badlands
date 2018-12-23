#include "Character.h"

#include <iostream>
#include <vector>

void PC::printInventory()
{
	std::cout << "You have a ";
	for (std::vector<Object*>::iterator it = getInventory().begin(), end = getInventory().end(); it != end; ++it) {
		std::cout << (*it)->getName();
		if (&(*it) != &(getInventory().back()))
		{
			if (&(*(++it)) == &(getInventory().back()))	// Temporarily increment it to check the next item.
			{
				std::cout << " and a ";
				--it;									// Reverse temporary increment.
			}
			else
			{
				--it;									// Reverse temporary increment.
				std::cout << ", a ";
			}
		}
	}
	std::cout << "." << std::endl;
}