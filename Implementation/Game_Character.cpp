#include "Game_Character.h"

void PC::printInventory()
{
	std::cout << "You have " << getGold() << " gold.\n";
	std::cout << "You have a ";
	for (std::vector<Object*>::iterator it = getInventory().begin(), end = getInventory().end(); it != end; ++it) {
		std::cout << (*it)->getName();
		if (&(*it) != &(getInventory().back()))
		{
			if (&(*(++it)) == &(getInventory().back()))	// Temporarily increment it to check the next item.
			{
				std::cout << " and a ";
				--it;									// Reverse temporary increment.
			}
			else
			{
				--it;									// Reverse temporary increment.
				std::cout << ", a ";
			}
		}
	}
	std::cout << "." << std::endl;
}



/*
	level
Start at level 1.
11 is the highest.
Leveling up:
X Add one to a base trait (total of 11 possible added)
O Learn/improve a skill? How do skills work? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Divide a number of points among derived traits as bonuses (This increases as they level up)
- Gain a new special ability on certain levels (this is probably class-dependent)

Derived Bonus Points | Level
LVL| BONUS
01 | 0
02 | 1
03 | 2
04 | 2
05 | 3
06 | 3
07 | 4
08 | 4
09 | 5
10 | 5
11 | 6

35 Total additional points

Base traits:
st, dx, iq, ht
*/
void PC::levelUp()
{
	static const unsigned short derivedBonusArray[] =
	{
		0,			/* Level 00 - 0 bonus derived points as this level doesn't exist	*/
		0,			/* Level 01 - 0 bonus derived points as this is the starting level	*/
		1,			/* Level 02 - 1 bonus derived point									*/
		2,			/* Level 03 - 2 bonus derived points								*/
		2,			/* Level 04 - 2 bonus derived points								*/
		3,			/* Level 05 - 3 bonus derived points								*/
		3,			/* Level 06 - 3 bonus derived points								*/
		4,			/* Level 07 - 4 bonus derived points								*/
		4,			/* Level 08 - 4 bonus derived points								*/
		5,			/* Level 09 - 5 bonus derived points								*/
		5,			/* Level 10 - 5 bonus derived points								*/
		6			/* Level 11 - 5 bonus derived points								*/
	};

	incrementLevel();
	std::cout << "Level up!\n"\
		<< "You are now level " << getLvl() << ".\n\n";

	// TODO: Give the user an opportunity to use any saved primary stats points.
	/* Increase a Primary Stat */
	std::string response = "";
	std::cout << "Please pick a base trait you'd like to increase by one point:\n" \
		<< "    strength\n    dexterity\n    intelligence\n    health\n" \
		<< "Enter \"none\" to save it for later.\n";

	while ((response != "strength") && (response != "dexterity") && (response != "intelligence") && (response != "health") && (response != "none"))
	{
		std::cin >> response;
	}
	if (response == "strength")
	{
		incrementSt();
	}
	else if (response == "dexterity")
	{
		incrementDx();
	}
	else if (response == "intelligence")
	{
		incrementIq();
	}
	else if (response == "health")
	{
		incrementHt();
	}
	else if (response == "none")
	{
		savePrimaryStatPoint();
	}

	// TODO: Balance the derived bonus points (this may take play testing)
	unsigned short derivedBonusPoints = derivedBonusArray[getLvl()] + getSavedDerivedStatPoints();
	if (getLvl() == 2)
	{
		std::cout << "You have received a derived stat bonus point. As you level up,"\
			<< " you will recieve additional derived stat bonus points in increasing quantities:\n"\
			<< "    2 points at levels 3 and 4\n    3 points at levels 5 and 6\n"\
			<< "    4 points at levels 7 and 8\n    5 points at levels 9 and 10\n    6 points at level 11\n\n";
	} // TODO: It would be nice if the user could access these values. Also, a lot of this implementation-specific stuff might be better left
	  // to the customer. A barebones framework with an API for setting all of these values may be better.
	else
		std::cout << "You have " << derivedBonusPoints << "bonus point(s) to divide among your derived stats.\n\n";

	for (int i = 0; i < derivedBonusPoints; i++)
	{
		response = "";
		std::cout << "Please pick a derived stat you'd like to increase:\n" \
			<< "    max hit points\n    speed\n    melee accuracy\n    melee damage\n    ranged accuracy\n    ranged damage\n" \
			<< "Enter \"none\" to save it for later.\n";

		while ((response != "max hit points")
			&& (response != "speed")
			&& (response != "melee accuracy")
			&& (response != "melee damage")
			&& (response != "ranged accuracy")
			&& (response != "ranged damage")
			&& (response != "none"))
		{
			std::cin >> response;
		}
		if (response == "max hit points")
		{
			incrementMaxHp();
		}
		if (response == "speed")
		{
			incrementSpeed();
		}
		else if (response == "melee accuracy")
		{
			incrementMeleeAcc();
		}
		else if (response == "melee damage")
		{
			incrementMeleeDamage();
		}
		else if (response == "ranged accuracy")
		{
			incrementRangedAcc();
		}
		else if (response == "ranged damage")
		{
			incrementRangedDmg();
		}
		else if (response == "none")
		{
			saveDerivedStatPoint();
		}
	}

	/* Heal character to full health */
	healFull();

	// TODO: Learn/Improve a skill

	// TODO: Learn/Improve a special ability on certain levels

	// TODO: The above two todos probably indicate that class-specific level up functions should be written for each class, which handle these.

	// TODO: This should all be implemented at the design level.

	/* TODO: Enable this method to be called from a "use saved points" or "level up" or some such command. Communicate this functionality
		to the user whenever they choose to save the point for later. */

	printCharacterSheet();
}


void PC::printStatus()
{
	std::cout << "You are ";
	switch (getStatus())
	{
	case STATUS_NONE:
	{
		std::cout << "fine.\n";
		break;
	}
	case STATUS_DIRTY:
	{
		std::cout << "dirty.\n";
		break;
	}
	case STATUS_DEAD:
	{
		std::cout << "dead.\n";
		break;
	}
	case STATUS_UNCONSCIOUS:
	{
		std::cout << "unconscious.\n";
		break;
	}
	case STATUS_HIDDEN:
	{
		std::cout << "hidden.\n";
		break;
	}
	case STATUS_CONFUSED:
	{
		std::cout << "confused.\n";
		break;
	}
	case STATUS_BURNED:
	{
		std::cout << "burned.\n";
		break;
	}
	case STATUS_POISONED:
	{
		std::cout << "poisoned.\n";
		break;
	}
	case STATUS_FROZEN:
	{
		std::cout << "frozen.\n";
		break;
	}
	case STATUS_RECOILING:
	{
		std::cout << "recoiling.\n";
		break;
	}
	case STATUS_BLEEDING:
	{
		std::cout << "bleeding.\n";
		break;
	}
	case STATUS_HUNGRY:
	{
		std::cout << "hungry.\n";
		break;
	}
	}
}

void PC::printCharacterSheet()
{
	std::cout << "Your name is " << getName() << ".\n"
		<< "You are a level " << getLvl() << " " << /*TODO: getRace*/ "mutant " << /*" " TODO: getClass*/ "wanderer.\n"
		<< "You have " << getXp() << " experience points.\n" // TODO: Exp to next level
		<< "You are " << getStatus() << ".\n"
		<< "Your primary stats are as follows:\n"
		<< "   Strength    : " << getSt()
		<< "   Dexterity   : " << getDx()
		<< "   Intelligence: " << getIq()
		<< "   Health      : " << getHt();
	// TODO: Finish Me.
}