/***********************************************************************
// File: team.h
// Date: Oct 8,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <iostream>
#include <cstring>
#include "abilities.h"
#include "weapons.h"
#include "health.h"
#include "character.h"

using namespace std;

namespace seneca {
	class Team 
	{
		string m_teamName;		// A string with the name of this team
		Character** m_character; // This class should store the address of the array
		size_t m_numCharacter;	// Current number of character
		size_t m_capacity;		// Capacity of the character

	public:

	// Default Constructor
		Team();
	// Constructor
		Team(const char* name);
	// Destructor
		~Team();

	// Copy Constructor
		Team(const Team& other);
	// Copy Assignment Operator
		Team& operator=(const Team& other);

	// Move Constructor
		Team(Team&& other) noexcept;
	// Move Assignment Operator
		Team& operator=(Team&& other) noexcept;
	
	// Function that adds the character received as parameter to the team ONLY IF the team doesn't have a character with the same name.
		void addMember(const Character* c);

	// Function that searches the team for a character with the name received as parameter and removes it from the team.
		void removeMember(const std::string& c);

	//  Funtion that returns the character ar the index specified as parameter, or null if the index is out of bounds.
		Character* operator[](size_t idx) const;

	// Function that prints to screen the content of current object
		void showMembers() const;


	};
}

#endif