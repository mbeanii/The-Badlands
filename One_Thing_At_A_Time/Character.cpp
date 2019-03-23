#include "Character.h"

#include <iostream>
#include <vector>

void Character::addMaxHp(unsigned short inputMaxHp)
{
	derivedStatsBonus.maxHp += inputMaxHp;
	calculateDerivedStats();
}

void Character::incrementMaxHp()
{
	derivedStatsBonus.maxHp++;
	calculateDerivedStats();
}

void Character::addCurrentHp(unsigned short inputCurrentHp)
{
	derivedStatsBonus.currentHp += inputCurrentHp;
	calculateDerivedStats();
}

void Character::addSpeed(unsigned short inputSpeed)
{
	derivedStatsBonus.speed += inputSpeed;
	calculateDerivedStats();
}

void Character::incrementSpeed()
{
	derivedStatsBonus.speed++;
	calculateDerivedStats();
}

void Character::addMeleeAcc(unsigned short inputMeleeAcc)
{
	derivedStatsBonus.meleeAcc += inputMeleeAcc;
	calculateDerivedStats();
}

void Character::incrementMeleeAcc()
{
	derivedStatsBonus.meleeAcc++;
	calculateDerivedStats();
}

void Character::addMeleeDamage(unsigned short inputMeleeDmg)
{
	derivedStatsBonus.meleeDmg += inputMeleeDmg;
	calculateDerivedStats();
}

void Character::incrementMeleeDamage()
{
	derivedStatsBonus.meleeDmg++;
	calculateDerivedStats();
}

void Character::addRangedAcc(unsigned short inputRangedAcc)
{
	derivedStatsBonus.rangedAcc += inputRangedAcc;
	calculateDerivedStats();
}

void Character::incrementRangedAcc()
{
	derivedStatsBonus.rangedAcc++;
	calculateDerivedStats();
}

void Character::addRangedDmg(unsigned short inputRangedDmg)
{
	derivedStatsBonus.rangedDmg += inputRangedDmg;
	calculateDerivedStats();
}

void Character::incrementRangedDmg()
{
	derivedStatsBonus.rangedDmg++;
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

void Character::addAttacks(AttackEnables inputAttacks)
{
	if (inputAttacks.hasMeleeAttack == true)
	{
		attacks.hasMeleeAttack = true;
	}
	if (inputAttacks.hasItemAttack == true)
	{
		attacks.hasItemAttack = true;
	}
	if (inputAttacks.hasRangedAttack == true)
	{
		attacks.hasRangedAttack = true;
	}
	if (inputAttacks.hasSkillAttack == true)
	{
		attacks.hasSkillAttack = true;
	}
	if (inputAttacks.hasSpecialAttack == true)
	{
		attacks.hasSpecialAttack = true;
	}
}

void Character::removeAttacks(AttackEnables inputAttacks)
{
	if (inputAttacks.hasMeleeAttack == false)
	{
		attacks.hasMeleeAttack = false;
	}
	if (inputAttacks.hasItemAttack == false)
	{
		attacks.hasItemAttack = false;
	}
	if (inputAttacks.hasRangedAttack == false)
	{
		attacks.hasRangedAttack = false;
	}
	if (inputAttacks.hasSkillAttack == false)
	{
		attacks.hasSkillAttack = false;
	}
	if (inputAttacks.hasSpecialAttack == false)
	{
		attacks.hasSpecialAttack = false;
	}
}
