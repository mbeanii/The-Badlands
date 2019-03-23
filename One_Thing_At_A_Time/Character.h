#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.h"

/* Enumerations */
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

enum Character_Stat_Type
{
	STAT_NONE,					/* None					*/
	STAT_ST,					/* Strenth				*/
	STAT_DX,					/* Dexterity			*/
	STAT_IQ,					/* Intelligence			*/
	STAT_HT,					/* Health				*/
	STAT_MAX_HP,				/* Maximum Hit Points	*/
	STAT_SPEED,					/* Speed				*/
	STAT_MELEE_ACC,				/* Melee Accuracy		*/
	STAT_MELEE_DMG,				/* Melee Damage			*/
	STAT_RANGED_ACC,			/* Ranged Accuracy		*/
	STAT_RANGED_DMG,			/* Ranged Damage		*/
	STAT_IS_STUCK,				/* Is Stuck				*/
	STAT_IS_DEAD,				/* Is Dead				*/
	STAT_MAX_CHARACTER_STAT		/* Maximum number		*/
};

/* Structs */

struct PrimaryStats
{
	/* Primary Stats */
	/* Strength */
	unsigned short st;
	/* Dexterity */
	unsigned short dx;
	/* Intelligence */
	unsigned short iq;
	/* Health */
	unsigned short ht;
};

struct DerivedStats
{
	/* Maximum Hit Points */
	unsigned short maxHp;
	/* Current Hit Points */
	unsigned short currentHp;
	/* Speed */
	unsigned short speed;
	/* Melee Accuracy */
	unsigned short meleeAcc;
	/* Melee Damge */
	unsigned short meleeDmg;
	/* Ranged Accuracy */
	unsigned short rangedAcc;
	/* Ranged Damage */
	unsigned short rangedDmg;
};

struct SpecialAbility
{
	std::string name;
	Target_Type target;
	std::vector<Character_Stat_Type> statsAffected;
	int duration;
	int usesPerDay;
	bool isAnAttack;
};

/* The number of each type of character points a character has saved for later. */
struct SavedCharacterPoints
{
	unsigned short primaryStats;
	unsigned short derivedStats;
	unsigned short specialAbility;
};

/* Boolean variables identifying which attack types are available. An attack is any ability that is usable in combat. */
struct AttackEnables
{
	bool isAttackOff;			/* Character is unable to attack.										*/
	bool hasMeleeAttack;		/* Character has a melee attack.										*/
	bool hasRangedAttack;		/* Character has a ranged attack.										*/
	bool hasSpecialAttack;		/* Character has a special ability with an attack.						*/
	bool hasSkillAttack;		/* Character has a skill with an attack.								*/
	bool hasItemAttack;			/* Character has an item with an attack (e.g., cloak, magic ring, etc.	*/
};

class Skill
{
public:
	std::string name;
	int skillLevel;
	Target_Type target;
	std::vector<Character_Stat_Type> statsAffected;
	bool isAnAttack;
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
	unsigned int gold;

	/* Experience points */
	unsigned int xp;
	/* Level */
	unsigned short lvl;

	/* Primary Stats */
	PrimaryStats primaryStats;

	/* Derived Stats */
	DerivedStats derivedStats; /* TODO: Add Armor Class */

	void calculateDerivedStats(); // TODO: Write this

	/* Derived Stat Bonuses */
	DerivedStats derivedStatsBonus;

	/* Boolean variables identifying which attack types are available. */
	AttackEnables attacks;

	/* Special Abilities */
	std::vector<SpecialAbility> specialAbilities;

	/* Stored Level Up Points */
	SavedCharacterPoints savedCharacterPoints;

	
public:
	/* Constructors */
	Character() {}
	Character(std::string inputName, Status_Type inputStatus) : name(inputName), status(inputStatus) {}
	// TODO: Write nondefault constructor with full stats list. Character(std::string inputName, Status_Type inputStatus );

	/* Accessors */
	std::string getName() { return name; }
	const Status_Type getStatus() { return status; }
	std::vector<Object*> & getInventory() { return inventory; }
	unsigned int getGold() { return gold; }
	unsigned int getXp() { return xp; }
	unsigned short getLvl() { return lvl; }
	unsigned short getSt() { return primaryStats.st; }
	unsigned short getDx() { return primaryStats.dx; }
	unsigned short getIq() { return primaryStats.iq; }
	unsigned short getHt() { return primaryStats.ht; }
	unsigned short getMaxHp() { return derivedStats.maxHp; }
	unsigned short getCurrentHp() { return derivedStats.currentHp; }
	unsigned short getMeleeAcc() { return derivedStats.meleeAcc; }
	unsigned short getMeleeDmg() { return derivedStats.meleeDmg; }
	unsigned short getRangedAcc() { return derivedStats.rangedAcc; }
	unsigned short getRangedDmg() { return derivedStats.rangedDmg; }
	unsigned short getSpeed() { return derivedStats.speed; }
	std::vector<Skill *> getSkillList() { return skillList; }
	std::vector<SpecialAbility *> getSpecialAbilityList() { return specialAbilityList; }
	AttackEnables getAttacks() { return attacks; }
	unsigned short getSavedPrimaryStatPoints() { return savedCharacterPoints.primaryStats; }
	unsigned short getSavedDerivedStatPoints() { return savedCharacterPoints.derivedStats; }
	unsigned short getSavedSpecialAbilityPoints() { return savedCharacterPoints.specialAbility; }

	/* Mutators */
	void setName(std::string inputName) { name = inputName; }
	void setStatus(Status_Type inputStatus) { status = inputStatus; }
	void setInventory(std::vector<Object*> inputInventory) { inventory = inputInventory; }
	void pushInventory(Object *inputObject) { inventory.push_back(inputObject); }
	void addGold(unsigned int inputGold) { gold += inputGold; }
	void incrementLevel() { lvl++; }
	void addXp(unsigned int inputXp) { xp += inputXp; }
	void setSt(unsigned short inputSt) { primaryStats.st = inputSt; }
	void incrementSt() { primaryStats.st++; }
	void setDx(unsigned short inputDx) { primaryStats.dx = inputDx; }
	void incrementDx() { primaryStats.dx++; }
	void setIq(unsigned short inputIq) { primaryStats.iq = inputIq; }
	void incrementIq() { primaryStats.iq++; }
	void setHt(unsigned short inputHt) { primaryStats.ht = inputHt; }
	void incrementHt() { primaryStats.ht++; }
	void addMaxHp(unsigned short inputMaxHp);
	void incrementMaxHp();
	void addCurrentHp(unsigned short inputCurrentHp);
	void addSpeed(unsigned short inputSpeed);
	void incrementSpeed();
	void addMeleeAcc(unsigned short inputMeleeAcc);
	void incrementMeleeAcc();
	void addMeleeDamage(unsigned short inputMeleeDmg);
	void incrementMeleeDamage();
	void addRangedAcc(unsigned short inputRangedAcc);
	void incrementRangedAcc();
	void addRangedDmg(unsigned short inputRangedDmg);
	void incrementRangedDmg();
	void addAttacks(AttackEnables inputAttacks);	/* Adds each true attack value to the character's attacks */
	void removeAttacks(AttackEnables inputAttacks);	/* Removes each false attack value from the character's attacks */
	/* Set individual attack enables */
	void setMeleeAttack() { attacks.hasMeleeAttack = true; }
	void setItemAttack() { attacks.hasItemAttack = true; }
	void setRangedAttack() { attacks.hasRangedAttack = true; }
	void setSkillAttack() { attacks.hasSkillAttack = true; }
	void setSpecialAttack() { attacks.hasSpecialAttack = true; }
	/* Reset individual attack enables */
	void resetMeleeAttack() { attacks.hasMeleeAttack = false; }
	void resetItemAttack() { attacks.hasItemAttack = false; }
	void resetRangedAttack() { attacks.hasRangedAttack = false; }
	void resetSkillAttack() { attacks.hasSkillAttack = false; }
	void resetSpecialAttack() { attacks.hasSpecialAttack = false; }
	void savePrimaryStatPoint() { savedCharacterPoints.primaryStats++; }
	void saveDerivedStatPoint() { savedCharacterPoints.derivedStats++; }
	void saveSpecialAbilityPoint() { savedCharacterPoints.specialAbility++; }
	void healFull() { derivedStats.currentHp = derivedStats.maxHp; }
	void healPartial(unsigned short inputHp) { derivedStats.currentHp += inputHp; }

	// Virtual Utilities
	virtual void printInventory() {}
	virtual void printStatus() {};
	virtual void printCharacterSheet() {};
	virtual void levelUp() {}
};