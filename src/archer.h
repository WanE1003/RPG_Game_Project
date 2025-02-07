/***********************************************************************
// File: archer.h
// Date: Oct 8,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include "abilities.h"
#include "weapons.h"
#include "health.h"
#include "characterTpl.h"

using namespace std;

namespace seneca 
{
	// Weapon_t: the type implementing the weapons the barbarian will handle.
	template<typename Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth> // Archers do not have any special ability.
	{
		int m_baseAttack;	// The basic attack power
		int m_baseDefense;	// The basic defense
		Weapon_t m_weapon;	// The weapon the character can use in battle.

	public:
	// Constructor that initializes a new object to the values received as parameters.
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon) :
			CharacterTpl< SuperHealth>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_weapon(weapon) {};

	// A function that returns the damage that character can do in an attack.
		int getAttackAmnt() const
		{
			return 1.3 * m_baseAttack; // The weapon is ignored.
		}

	// A function that return the defense of this archer.
		int getDefenseAmnt() const
		{
			return 1.2 * m_baseDefense;
		}

	// A function that dynamically creates a copy of the current instance and returns its address to the client.
		Character* clone() const override
		{
			return new Archer(*this);
		}

	// A function that attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) override
		{
			cout << Character::getName() << " is attacking " << enemy->getName() << "." << endl;
			
			// Retrieve the damage this character can do using the function getAttackAmnt.
			int damage = getAttackAmnt();

			cout << "    " << "Archer deals " << damage << " ranged damage!" << endl;

			// Apply the damage to the enemy, by calling the takeDamage() function 
			enemy->takeDamage(damage);
		}

	// This function will modify the damage received using the defense capabilities.
		void takeDamage(int dmg) override
		{
			cout << Character::getName() << " is attacked for " << dmg << " damage." << endl;
			cout << "    " << "Archer has a defense of " << m_baseDefense << ". Reducing damage received." << endl;

			// Subtract the defense amount from the parameter.
			int newDamage = dmg - m_baseDefense;
			if (newDamage <= 0) // The new value cannot be less than 0.
			{
				newDamage = 1;
			}

			if (newDamage > this->getHealth())
			{
				newDamage = this->getHealth();
			}

			// Pass the calculated damage to update the health after taking damage.
			CharacterTpl<seneca::SuperHealth>::takeDamage(newDamage);
		}




	};
}

#endif // !SENECA_ARCHER_H
