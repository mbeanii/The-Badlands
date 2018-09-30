#include "Location.h"

bool Location::checkObjectIsHere(int object)
{
	for (std::vector<Object *>::iterator it = objectsHere.begin(); it != objectsHere.end(); ++it)
	{
		if ((*it)->id == object)
			return true;
	}
	return false;
}