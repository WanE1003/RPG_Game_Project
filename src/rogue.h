/***********************************************************************
// File: rogue.h
// Date: Oct 8,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include "character.h"
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
#include "health.h"

using namespace std;

namespace seneca
{
	// A rogue will always use a dagger as a wapon, and two special abilities.
	template<typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue : public CharacterTpl<T>
	{
		int m_baseAttack;				// The basic attack power of this character
		int m_baseDefense;				// The basic defense of this character.
		FirstAbility_t m_firstAbility;	// The first special ability of this character.
		SecondAbility_t m_secondAbility;// The second special ability of this character.
		seneca::Dagger m_weapon;		// The two weapons the character can use in battle.

	public:
	// Constructor that initializes a new object to the values received as parameters.
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
			: CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {};

	// A function that returns the damage that character can do in an attack.
		int getAttackAmnt() const
		{
			return static_cast<int>(m_baseAttack + static_cast<double>(m_weapon) * 2);	
		}

	// A function that return the base defense value.
		int getDefenseAmnt() const
		{
			return m_baseDefense;
		}
	
	// A function that dynamically creates a copy of the current instance and returns its address to the client.
		Character* clone() const override
		{
			return new Rogue(*this);
		}

	// A function that attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) override
		{
			cout << Character::getName() << " is attacking " << enemy->getName() << "." << endl;

			// Use the first special ability to activate any beneficial effects on self.
			m_firstAbility.useAbility(this);

			// Use the second special ability to activate any beneficial effects on self.
			m_secondAbility.useAbility(this);

			// Retrieve the damage
			int damage = getAttackAmnt();

			// Enhance the damage dealt with any effects that the first special ability could apply.
			m_firstAbility.transformDamageDealt(damage);

			// Enhance the damage dealt with any effects that the second special ability could apply.
			m_secondAbility.transformDamageDealt(damage);

			cout << "Rogue deals " << damage << " melee damage!" << endl;

			// Apply the damage to the enemy
			enemy->takeDamage(damage);
		}
	// This function will modify the damage received using the defense capabilities and the special abilities, before calling the base class member to update the health.
		void takeDamage(int dmg) override
		{
			cout << Character::getName() << " is attacked for " << dmg << " damage." << endl;
			cout << "    " << "Rogue has a defense of " << m_baseDefense << ".Reducing damage received." << endl;

			// Subtract the defense amount from the parameter.
			int newDamage = dmg - m_baseDefense;
			if (newDamage <= 0) // The new value cannot be less than 0.
			{
				newDamage = 1;
			}

			// Use the first special ability to further reduce the damage taken.
			m_firstAbility.transformDamageReceived(newDamage);

			// Use the second special ability to further reduce the damage taken.
			m_secondAbility.transformDamageReceived(newDamage);

			if (newDamage > this->getHealth())
			{
				newDamage = this->getHealth();
			}

			CharacterTpl<T>::takeDamage(newDamage);
		}

	};
}


#endif // !SENECA_ROGUE_H
