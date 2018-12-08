#include "Location.h"
#include "assert.h" /* For assert */
#include <iostream> /* For cout */

/* Private functions */
Object *Location::lookupObjectByName(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->getName() == objectName)
			return (*it);
	}

	/* If object was not in the list */
	return NULL;
}

/* Public functions */

bool Location::checkObjectIsHere(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->getName() == objectName)
			return true;
	}
	return false;
}

void Location::removeObject(std::string inputObjectName) {

	Object *pInputObject = lookupObjectByName(inputObjectName);

	pInputObject->setRemoveMe(true);
	objectsHere.erase(remove_if(getObjectsHereBegin(), getObjectsHereEnd(), [](Object *lhs) {return lhs->getRemoveMe() == true; }));
	pInputObject->setRemoveMe(false);
};