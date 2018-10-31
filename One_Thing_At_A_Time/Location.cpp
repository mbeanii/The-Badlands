#include "Location.h"


/* Private functions */


Object *Location::lookupObjectFromName(std::string objectName)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->getName() == objectName)
			return (*it);
	}
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

OBJECTS_ENUM Location::removeObject(std::string inputObjectName) {

	Object *pInputObject = lookupObjectFromName(inputObjectName);

	// Return the object ID so we can add one to the masterObjectList
	OBJECTS_ENUM returnValue = pInputObject->getId();

	pInputObject->setRemoveMe(true);
	objectsHere.erase(remove_if(getObjectsHereBegin(), getObjectsHereEnd(), [](Object *lhs) {return lhs->getRemoveMe() == true; }));
	pInputObject->setRemoveMe(false);

	return returnValue;
};