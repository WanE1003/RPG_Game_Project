/***********************************************************************
// File: barbarian.h
// Date: Oct 8,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include <iomanip>
#include <string>
#include "character.h"
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
#include "health.h"

using namespace std;

namespace seneca
{
	// T: the type of the object storing the health.
	// Ability_t: the type implementing the special abilities that this barbarian has.
	// Weapon_t: the type implementing the weapons the barbarian will handle.
	template<typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T>
	{
		int m_baseAttack;	// The basic attack power
		int m_baseDefense;	// The basic defense
		Ability_t m_ability;// The special ability
		Weapon_t m_weapon[2];	// The two weapons the character can use in battle.

	public:
	// Constructor that initializes a new object to the values received as parameters.
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
			: CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) 
		{
			m_weapon[0] = primaryWeapon;
			m_weapon[1] = secondaryWeapon;
		};

	// A function that returns the damage that character can do in an attack.
		int getAttackAmnt() const
		{
			return static_cast<int>(m_baseAttack + static_cast<double>(m_weapon[0])/2 + static_cast<double>(m_weapon[1])/2);
		}

	// A function that return the base defense value.
		int getDefenseAmnt() const
		{
			return m_baseDefense;
		}

	// A function that dynamically creates a copy of the current instance and returns its address to the client.
		Character* clone() const override
		{
			return new Barbarian(*this); // Creates a copy of the current instance
		}

	// A function that attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) override
		{
			cout << Character::getName() << " is attacking " << enemy->getName() << "." << endl;

			// Use the special ability to activate any beneficial effects on self.
			m_ability.useAbility(this);

			// Retrieve the damage this character using the function getAttackAmnt.
			int damage = getAttackAmnt(); 

			// Enhance the damage dealt with any effects that the special ability could apply.
			m_ability.transformDamageDealt(damage);

			cout << "    " << "Barbarian deals " << damage << " melee damage!" << endl;

			// Apply the damage to the enemy, by calling the takeDamage() function
			enemy->takeDamage(damage);
		}

	// This function will modify the damage received using the defense capabilities and the special ability.
		void takeDamage(int dmg) override
		{
			cout << Character::getName() << " is attacked for " << dmg << " damage." << endl;
			cout << "    " << "Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << endl;

			// Subtract the defense amount from the parameter.
			int newDamage = dmg - m_baseDefense;
			if (newDamage <= 0) // The new value cannot be less than 0.
			{
				newDamage = 1;
			}

			// Use the special ability to further reduce the damage taken.
			m_ability.transformDamageReceived(newDamage); 

			if (newDamage > this->getHealth())
			{
				newDamage = this->getHealth();
			}

			CharacterTpl<T>::takeDamage(newDamage);
			
		}


	};
}


#endif // !SENECA_BARBARIAN_H
