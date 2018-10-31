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

void Location::removeObject(std::string inputObjectName) {

	Object *pInputObject = lookupObjectFromName(inputObjectName);

	pInputObject->setRemoveMe(true);
	objectsHere.erase(remove_if(getObjectsHereBegin(), getObjectsHereEnd(), [](Object *lhs) {return lhs->getRemoveMe() == true; }));
	pInputObject->setRemoveMe(false);
};