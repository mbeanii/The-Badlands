#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.h"

enum Status_Type
{
	STATUS_NONE,
	STATUS_DIRTY,
	STATUS_DEAD,
	STATUS_UNCONSCIOUS,
	STATUS_HIDDEN,
	STATUS_CONFUSED,
	STATUS_BURNED,
	STATUS_POISONED,
	STATUS_FROZEN,
	STATUS_RECOILING,
	STATUS_BLEEDING,
	STATUS_HUNGRY
};

enum Target_Type
{
	TARGET_NONE,
	TARGET_SELF,
	TARGET_SINGLE_CHARACTER,
	TARGET_GROUP,
	TARGET_AREA_EFFECT,
	TARGET_LOCATION,
	TARGET_FEATURE,
	TARGET_ITEM,
	MAX_TARGET
};

struct PrimaryStats
{
	/* Primary Stats */
	/* Strength */
	int st;
	/* Dexterity */
	int dx;
	/* Intelligence */
	int iq;
	/* Health */
	int ht;
};

struct DerivedStats
{
	/* Maximum Hit Points */
	int maxHp;
	/* Current Hit Points */
	int currentHp;
	/* Speed */
	int speed;
	/* Melee Accuracy */
	int meleeAcc;
	/* Melee Damge */
	int meleeDmg;
	/* Ranged Accuracy */
	int rangedAcc;
	/* Ranged Damage */
	int rangedDmg;
};

enum Character_Stat
{
	CHARACTER_STAT_NONE,	/* None					*/
	ST,						/* Strenth				*/
	DX,						/* Dexterity			*/
	IQ,						/* Intelligence			*/
	HT,						/* Health				*/
	MAX_HP,					/* Maximum Hit Points	*/
	SPEED,					/* Speed				*/
	MELEE_ACC,				/* Melee Accuracy		*/
	MELEE_DMG,				/* Melee Damage			*/
	RANGED_ACC,				/* Ranged Accuracy		*/
	RANGED_DMG,				/* Ranged Damage		*/
	IS_STUCK,				/* Is Stuck				*/
	IS_DEAD,				/* Is Dead				*/
	MAX_CHARACTER_STAT		/* Maximum number		*/
};

struct SpecialAbility
{
	std::string name;
	Target_Type target;
	std::vector<Character_Stat> statsAffected;
	int duration;
	int usesPerDay;
};

class Skill
{
public:
	std::string name;
	int skillLevel;
	Target_Type target;
	std::vector<Character_Stat> statsAffected;
	unsigned int turnDuration;
	int damage;
	unsigned short usesPerDay;
	virtual void useSkill() {};
};

class Character
{
private:
	std::string name;
	Status_Type status;
	std::vector<Object *> inventory;
	std::vector<Skill *> skillList;
	std::vector<SpecialAbility *> specialAbilityList;
	int gold;

	/* Experience points */
	int xp;
	/* Level */
	int lvl;

	/* Primary Stats */
	PrimaryStats primaryStats;

	/* Derived Stats */
	DerivedStats derivedStats;

	/* Derived Stat Bonuses */
	DerivedStats derivedStatsBonus;

	std::vector<SpecialAbility> specialAbilities;
	void calculateDerivedStats();
	
public:
	/* Constructors */
	Character() {}
	Character(std::string inputName, Status_Type inputStatus) : name(inputName), status(inputStatus) {}

	/* Accessors */
	std::string getName() { return name; }
	const Status_Type getStatus() { return status; }
	std::vector<Object*> & getInventory() { return inventory; }
	int getGold() { return gold; }
	int getXp() { return xp; }
	int getLvl() { return lvl; }
	int getSt() { return primaryStats.st; }
	int getDx() { return primaryStats.dx; }
	int getIq() { return primaryStats.iq; }
	int getHt() { return primaryStats.ht; }
	int getMaxHp() { return derivedStats.maxHp; }
	int getCurrentHp() { return derivedStats.currentHp; }
	int getMeleeAcc() { return derivedStats.meleeAcc; }
	int getMeleeDmg() { return derivedStats.meleeDmg; }
	int getRangedAcc() { return derivedStats.rangedAcc; }
	int getRangedDmg() { return derivedStats.rangedDmg; }
	int getSpeed() { return derivedStats.speed; }
	std::vector<Skill *> getSkillList() { return skillList; }
	std::vector<SpecialAbility *> getSpecialAbilityList() { return specialAbilityList; }


	/* Mutators */
	void setName(std::string inputName) { name = inputName; }
	void setStatus(Status_Type inputStatus) { status = inputStatus; }
	void setInventory(std::vector<Object*> inputInventory) { inventory = inputInventory; }
	void pushInventory(Object *inputObject) { inventory.push_back(inputObject); }
	void addGold(int inputGold) { gold += inputGold; }
	void addXp(int inputXp) { xp += inputXp; }
	void levelUp(); // TODO: Write levelUp()
	void setSt(int inputSt) { primaryStats.st = inputSt; }
	void setDx(int inputDx) { primaryStats.dx = inputDx; }
	void setIq(int inputIq) { primaryStats.iq = inputIq; }
	void setHt(int inputHt) { primaryStats.ht = inputHt; }
	void addMaxHp(int inputMaxHp);
	void addCurrentHp(int inputCurrentHp);
	void addSpeed(int inputSpeed); 
	void addMeleeAcc(int inputMeleeAcc);
	void addMeleeDamage(int inputMeleeDmg);
	void addRangedAcc(int inputRangedAcc);
	void addRangedDmg(int inputRangedDmg);

	// Virtual Utilities
	virtual void printInventory() {}
	virtual void printStatus();
};

class PC : public Character
{
public:
	PC() { setName("pc"), setStatus(STATUS_DIRTY); }

	// Virtual Utilities
	void printInventory();
};