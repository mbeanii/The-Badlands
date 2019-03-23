#pragma once

#include "character.h"

/* TODO: Determine whether there will be a PC class or not.
 * If so, move level up, and any other appropriate functions to the PC class
 * If not, move printInventory to the Character class and remove the character class.
 * I think I DO want an inherited PC class
 * And probably an inherited hostile class, and inherited playable character classes, or party character class or the like.
 * I'm also thinking these should be at the application level, rather than at the framework/driver level. Thus, there's an effort to move it.
 */
class PC : public Character
{
public:
	// Constructors
	PC() { setName("pc"), setStatus(STATUS_DIRTY); }

	// Utilities
	void printInventory();
	void printStatus();
	void printCharacterSheet(); // TODO: Write this.
	void levelUp();
};