#pragma once

#include <string>

class Object
{
private:
	std::string name;
	std::string description;
	bool removeMe;
	std::vector<std::string> actionList;

public:
	/* Accessors */
	std::string getName() { return name; }
	std::string getDescription() { return description; }
	bool getRemoveMe() { return removeMe; }
	std::vector<std::string> getActionList() { return actionList; }

	/* Mutators */
	void setName(std::string inputName) { name = inputName; }
	void setDescription(std::string inputDescription) { description = inputDescription; }
	void setRemoveMe(bool inputRemoveMe) { removeMe = inputRemoveMe; }
	void addAction(std::string inputAction) { actionList.push_back(inputAction); }
	void emptyActionList() { actionList = {}; }

	/* Constructors */
	Object(std::string inputName, std::string inputDescription, std::vector<std::string> inputActionList) : name(inputName), description(inputDescription), removeMe(false), actionList(inputActionList) {}
	Object() : name(""), description(""), removeMe(false), actionList({ "use" }) {}
};