#pragma once

#include <string>

enum OBJECTS { WATER, SWORD, CAT };

class Object
{
public:
	std::string name;
	std::string compareObjectName; // Used to compare a different object to this object
	std::string description;
	int id;
};