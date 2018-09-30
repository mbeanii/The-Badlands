#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.h"

class Character
{
public:
	std::string status;
	std::vector<Object*> inventory;
};

class PC : public Character
{
public:
	PC() { status = "dirty"; }

	void printPCStatus() { std::cout << "You are " << status << "." << std::endl; }
	void printInventory();
};