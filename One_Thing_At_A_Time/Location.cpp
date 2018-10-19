#include "Location.h"


/* Private functions */


Object *Location::lookupObjectFromName(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->name == objectName)
			return (*it);
	}
}

/* Public functions */

bool Location::checkObjectIsHere(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->name == objectName)
			return true;
	}
	return false;
}

OBJECTS Location::removeObject(std::string inputObjectName) {

	Object *pInputObject = lookupObjectFromName(inputObjectName);

	// Return the object ID so we can add one to the masterObjectList
	OBJECTS returnValue = pInputObject->id;

	pInputObject->removeMe = true;
	objectsHere.erase(remove_if(getObjectsHereBegin(), getObjectsHereEnd(), [](Object *lhs) {return lhs->removeMe == true; }));
	pInputObject->removeMe = false;

	return returnValue;
};