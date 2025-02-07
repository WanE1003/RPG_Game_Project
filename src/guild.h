/***********************************************************************
// File: guild.h
// Date: Oct 9,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <iostream>
#include <cstring>
#include "abilities.h"
#include "weapons.h"
#include "health.h"
#include "character.h"
#include "team.h"

using namespace std;

namespace seneca
{
	class Guild 
	{
		string m_guildName;
		Character** m_character;
		size_t m_numCharacter;
		size_t m_capacity;

	public:
		// Default Constructor
		Guild();
		// Constructor
		Guild(const char* name);
		// Destructor
		~Guild();

		// Copy Constructor
		Guild(const Guild& other);
		// Copy Assignment Operator
		Guild& operator=(const Guild& other);

		// Move Constructor
		Guild(Guild&& other) noexcept;
		// Move Assignment Operator
		Guild& operator=(Guild&& other) noexcept;

		// Function that adds the character received as parameter to the guild ONLY IF it's not already in the guild.
		void addMember(Character* c);

		// Function that searches the team for a character with the name received as parameter and removes it from the team.
		void removeMember(const std::string& c);

		// Function that returns the character at the index specified as parameter, or null if the index is out of bounds.
		Character* operator[](size_t idx) const;

		// Function that prints to screen the content of current object.
		void showMembers() const;

	};
}

#endif // SENECA_GUILD_H

