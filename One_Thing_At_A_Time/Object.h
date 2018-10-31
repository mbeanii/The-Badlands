#pragma once

#include <string>

enum OBJECTS_ENUM { WATER, SWORD, CAT };

class Object
{
private:
	std::string name;
	std::string description;
	bool removeMe;
	OBJECTS_ENUM id;

public:
	/* Accessors */
	std::string getName() { return name; };
	std::string getDescription() { return description; };
	OBJECTS_ENUM getId() { return id; };
	bool getRemoveMe() { return removeMe; };

	/* Mutators */
	void setName(std::string inputName) { name = inputName; };
	void setDescription(std::string inputDescription) { description = inputDescription; };
	void setId(OBJECTS_ENUM inputId) { id = inputId; };
	void setRemoveMe(bool inputRemoveMe) { removeMe = inputRemoveMe; };
};