#include "Character.h"

#include <iostream>
#include <vector>

void PC::printInventory()
{
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

inline void Character::addMaxHp(int inputMaxHp)
{
	derivedStatsBonus.maxHp += inputMaxHp;
	calculateDerivedStats();
}

inline void Character::addCurrentHp(int inputCurrentHp)
{
	derivedStatsBonus.currentHp += inputCurrentHp;
	calculateDerivedStats();
}

inline void Character::addSpeed(int inputSpeed)
{
	derivedStatsBonus.speed += inputSpeed;
	calculateDerivedStats();
}

inline void Character::addMeleeAcc(int inputMeleeAcc)
{
	derivedStatsBonus.meleeAcc += inputMeleeAcc;
	calculateDerivedStats();
}

inline void Character::addMeleeDamage(int inputMeleeDmg)
{
	derivedStatsBonus.meleeDmg += inputMeleeDmg;
	calculateDerivedStats();
}

inline void Character::addRangedAcc(int inputRangedAcc)
{
	derivedStatsBonus.rangedAcc += inputRangedAcc;
	calculateDerivedStats();
}

inline void Character::addRangedDmg(int inputRangedDmg)
{
	derivedStatsBonus.rangedDmg += inputRangedDmg;
	calculateDerivedStats();
}

void Character::calculateDerivedStats()
{ /* TODO: Computation */
	derivedStats.maxHp = /*Computation +*/ derivedStatsBonus.maxHp;
	derivedStats.currentHp = /*Computation +*/ derivedStatsBonus.currentHp;
	derivedStats.meleeAcc = /*Computation +*/ derivedStatsBonus.meleeAcc;
	derivedStats.meleeDmg = /*Computation +*/ derivedStatsBonus.meleeDmg;
	derivedStats.rangedAcc = /*Computation +*/ derivedStatsBonus.rangedAcc;
	derivedStats.meleeDmg = /*Computation +*/ derivedStatsBonus.meleeDmg;
	derivedStats.speed = /*Computation +*/ derivedStatsBonus.speed;
}

void Character::printStatus()
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