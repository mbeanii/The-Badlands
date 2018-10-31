#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for remove_if
#include "Object.h"

class Location
{
private:
	std::string name;
	std::string description;
	short row;
	short col;
	std::vector<Object *> objectsHere;

	Object *lookupObjectFromName(std::string objectName);

public:
	/* Accessors */
	std::string getName() { return name; };
	std::string getDescription() { return description; };
	std::vector<Object *> getObjectsHere() { return objectsHere; };
	std::vector<Object *>::iterator getObjectsHereBegin() { return objectsHere.begin(); }
	std::vector<Object *>::iterator getObjectsHereEnd() { return objectsHere.end(); }
	short getRow() { return row; };
	short getCol() { return col; };
	short getNextRow() { return (row + 1); };
	short getNextCol() { return (col + 1); };
	short getPrevRow() { return (row - 1); };
	short getPrevCol() { return (col - 1); };
	bool checkObjectIsHere(std::string objectName);

	/* Mutators */
	void setName(std::string inputName) { name = inputName; };
	void setDescription(std::string inputDescription) { description = inputDescription; };
	void setRow(short inputRow) { row = inputRow; };
	void setCol(short inputCol) { col = inputCol; };
	void pushObject(Object *pushee) { objectsHere.push_back(pushee); };
	void printLocationName() { std::cout << "You are at the " << name << "." << std::endl; }
	OBJECTS_ENUM removeObject(std::string pInputObject);
};