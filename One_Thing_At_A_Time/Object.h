#pragma once

#include <string>

class Object
{
private:
	std::string name;
	std::string description;
	bool removeMe;

public:
	/* Accessors */
	std::string getName() { return name; };
	std::string getDescription() { return description; };
	bool getRemoveMe() { return removeMe; };

	/* Mutators */
	void setName(std::string inputName) { name = inputName; };
	void setDescription(std::string inputDescription) { description = inputDescription; };
	void setRemoveMe(bool inputRemoveMe) { removeMe = inputRemoveMe; };

	/* Constructors */
	Object(std::string inputName, std::string inputDescription) : name(inputName), description(inputDescription), removeMe(false) {}
	Object() : name(""), description(""), removeMe(false) {};
};