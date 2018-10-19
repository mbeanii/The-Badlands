#pragma once

#include <string>

enum OBJECTS { WATER, SWORD, CAT };

class Object
{
public:
	std::string name;
	std::string description;
	bool removeMe;
	OBJECTS id;
};