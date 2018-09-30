#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.h"

class Character
{
private:
	std::string status;
	std::vector<Object*> inventory;
public:

	/* Accessors */
	const std::string & getStatus() { return status; };
	std::vector<Object*> & getInventory() { return inventory; };

	/* Mutators */
	void setStatus(std::string lhs) { status = lhs; };
	void setInventory(std::vector<Object*> lhs) { inventory = lhs; };
	void pushInventory(Object * lhs) { inventory.push_back(lhs); };
};

class PC : public Character
{
public:
	PC() { setStatus("dirty"); }

	void printPCStatus() { std::cout << "You are " << getStatus() << "." << std::endl; }
	void printInventory();
};