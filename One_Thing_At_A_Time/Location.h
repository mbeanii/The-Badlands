#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

class Location
{
public:
	std::string name;
	std::string description;
	short row;
	short col;
	std::vector<Object *> objectsHere;

	void printLocationName() { std::cout << "You are at the " << name << "." << std::endl; }
	bool checkObjectIsHere(int object);
};