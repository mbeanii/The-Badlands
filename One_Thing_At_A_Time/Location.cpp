#include "Location.h"
#include "assert.h" /* For assert */
#include <iostream> /* For cout */

/* Private functions */
Object *Location::lookupObjectHere(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->getName() == objectName)
			return (*it);
	}

	/* If object was not in the list */
	throw ("You can't see a ");
}

/* Public functions */

void Location::removeObject(std::string inputObjectName) {

	try
	{
		Object *pInputObject = lookupObjectHere(inputObjectName);
		pInputObject->setRemoveMe(true);
		objectsHere.erase(remove_if(getObjectsHereBegin(), getObjectsHereEnd(), [](Object *lhs) {return lhs->getRemoveMe() == true; }));
		pInputObject->setRemoveMe(false);
	}
	catch (const char* msg)
	{
		std::cerr << msg << inputObjectName << "in location: " << name << std::endl;
	}
};