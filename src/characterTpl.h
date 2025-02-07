/***********************************************************************
// WorkShop # 2
//
// File: characterTpl.h
// Date: Oct 8,2024
// Author:  Seungwan Hong
// Student ID:	167572221
// Seneca Email:   shong76@myseneca.ca
// -----------------------------------------------------------
// Name            Date            Reason
//
***********************************************************************/
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include <string>
#include <iostream>
#include "character.h"
#include "abilities.h"
/***********************************************************************
// File: characterTpl.h
// Date: Oct 7,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#include "weapons.h"
#include "health.h"

using namespace std;

namespace seneca {
	template<typename T>
	class CharacterTpl : public Character
	{
		int m_healthMax;	// The maximum health this character can have
		T m_health;			// The current health of the character. When this value gets to 0, the character died.

	public:

	// A custom constructor that receives the name of the character and the maximum health; 
	// Initializes the current instance with the values of the paameters and set the current health to maximum.
		CharacterTpl(const char* name, int maxHealth) 
			: Character(name), m_healthMax(maxHealth) 
		{
			m_health = maxHealth;
		};

	// A function that reduces the current health by the value of the parameter.
		void takeDamage(int dmg) override
		{
			m_health -= dmg;
			if (!isAlive()) // If the character died
			{
				cout << "    " <<  Character::getName() << " has been defeated!" << endl;
			}
			else if (Character::isAlive()) // If the character is still alive
			{
				cout << "    " << Character::getName() << " took " << dmg << " damage, " << m_health << " health remaining." << endl;
			}
		}

	// A function that returns current health. 
		int getHealth() const override
		{
			return static_cast<int>(m_health);
		}

	// A function that returns current maximum health.
		int getHealthMax() const override
		{
			return m_healthMax;
		}

	// A function that sets the current health to the value received as parameter.
		void setHealth(int health) override
		{
			m_health = health;
		}

	// A function that sets the maximum health and current health to the value of the parameter.
		void setHealthMax(int health) override
		{
			m_healthMax = health;
			m_health = health;
		}
	};
}

#endif // !SENECA_CHARACTERTPL_H
