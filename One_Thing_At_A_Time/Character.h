#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.h"

class Character
{
private:
	std::string name;
	std::string status;
	std::vector<Object*> inventory;
public:

	/* Accessors */
	const std::string & getStatus() { return status; };
	std::vector<Object*> & getInventory() { return inventory; };
	std::string getName() { return name; };

	/* Mutators */
	void setStatus(std::string lhs) { status = lhs; };
	void setInventory(std::vector<Object*> inputInventory) { inventory = inputInventory; };
	void pushInventory(Object *inputObject) { inventory.push_back(inputObject); };
	void setName(std::string inputName) { name = inputName; };

	// Virtual Utilities
	virtual void printInventory() {};
	virtual void printStatus() {};
};

class PC : public Character
{
public:
	PC() { setName("pc"), setStatus("dirty"); }

	// Virtual Utilities
	void printStatus() { std::cout << "You are " << getStatus() << "." << std::endl; }
	void printInventory();
};