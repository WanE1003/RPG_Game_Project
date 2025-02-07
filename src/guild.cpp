/***********************************************************************
// File: guild.cpp
// Date: Oct 9,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#include <iostream>
#include <iomanip>
#include "guild.h"

using namespace std;

namespace seneca
{
	// Constructor
	Guild::Guild(const char* name) : m_guildName(name), m_numCharacter(0), m_capacity(2) 
	{
		m_character = new Character * [m_capacity];
	};


	// Destructor
	Guild::~Guild()
	{

		delete[] m_character;
		m_character = nullptr;
	}

	// Copy Constructor
	Guild::Guild(const Guild& other) 
	{
		// copy resources
		m_guildName = other.m_guildName;
		m_numCharacter = other.m_numCharacter;
		m_capacity = other.m_capacity;

		// copy array of character (deep copy)
		if (m_capacity > 0)
		{
			m_character = new Character * [m_capacity]; // allocate memory
			for (size_t i = 0; i < m_numCharacter; i++) 
			{
				m_character[i] = other.m_character[i];
			}
		}
		else
		{
			m_character = nullptr;
		}
	}

	// Copy Assignment Operator
	Guild& Guild::operator=(const Guild& other)
	{
		if (this != &other)
		{
			// delete all objects
			for (size_t i = 0; i < m_numCharacter; i++)
			{
				delete m_character[i];
			}
			delete[] m_character;

			// copy resources
			m_guildName = other.m_guildName;
			m_numCharacter = other.m_numCharacter;
			m_capacity = other.m_capacity;

			// copy array of character (deep copy)
			if (m_capacity > 0)
			{
				m_character = new Character * [m_capacity]; // allocate memory
				for (size_t i = 0; i < m_numCharacter; i++)
				{
					m_character[i] = other.m_character[i]->clone();
				}
			}
			else
			{
				m_character = nullptr;
			}
		}
		return *this;
	}
	
	// Move Constructor
	Guild::Guild(Guild&& other) noexcept : m_guildName{}, m_character{}, m_numCharacter{}, m_capacity{}
	{
		// call move assignment operator
		*this = std::move(other);
	}


	// Move Assignment Operator
	Guild& Guild::operator=(Guild&& other) noexcept
	{
		if (this != &other)
		{
			// Deallocate dynamically allocated memory for each character
			for (size_t i = 0; i < m_numCharacter; i++)
			{
				delete m_character[i];
			}
			// Deallocate the entire character array memory
			delete[] m_character;

			// move resources
			m_guildName = move(other.m_guildName);
			m_character = other.m_character; //Moving the pointer itself
			m_numCharacter = other.m_numCharacter;
			m_capacity = other.m_capacity;

			// clean other object
			other.m_character = nullptr;
			other.m_numCharacter = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	// Function that adds the character received as parameter to the guild ONLY IF it's not already in the guild.
	void Guild::addMember(Character* c)
	{
		// test wether the guild have a character with the same name.
		for (size_t i = 0; i < m_numCharacter; i++)
		{
			if (m_character[i]->getName() == c->getName())
			{
				return; // same name found, don't add
			}
		}

		// Resize the array if necessary.
		if (m_numCharacter >= m_capacity)
		{
			m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;

			// Allocate a new temporary array
			Character** newCharacter = new Character * [m_capacity];

			// copy characters
			for (size_t i = 0; i < m_numCharacter; i++)
			{
				newCharacter[i] = m_character[i];
			}

			// Delete and replace existing array
			delete[] m_character;
			m_character = newCharacter;
		}

		// Add new character and add number of character
		m_character[m_numCharacter] = c;

		// Increase the max health of the character by 300 points.
		m_character[m_numCharacter]->setHealthMax(m_character[m_numCharacter]->getHealthMax() + 300);

		// Add number of character
		++m_numCharacter;
	}

	// Function that searches the team for a character with the name received as parameter and removes it from the team.
	void Guild::removeMember(const std::string& c)
	{
		for (size_t i = 0; i < m_numCharacter; i++)
		{
			// find character with same name
			if (m_character[i]->getName() == c)
			{
				// Decrease the max health of the character by 300 points.
				m_character[i]->setHealthMax(m_character[i]->getHealthMax() - 300);

				// Move the characters behind it to the front
				for (size_t j = i; j < m_numCharacter - 1; j++)
				{
					m_character[j] = m_character[j + 1];
				}

				// prevent unnecessary pointers
				m_character[m_numCharacter - 1] = nullptr;

				// reduce number of character
				--m_numCharacter;

				return;
			}
		}
	}

	// Function that returns the character at the index specified as parameter, or null if the index is out of bounds.
	Character* Guild::operator[](size_t idx) const
	{
		if (idx >= m_numCharacter)
		{
			return nullptr; // return nullptr if the index is out of range 
		}
		else
		{
			return m_character[idx]; // return character if index is valid
		}
	}

	// Function that prints to screen the content of current object.
	void Guild::showMembers() const
	{
		// Print it if there is no guild
		if (m_numCharacter == 0 && m_guildName.empty())
		{
			cout << "No guild." << endl;
			return;
		}

		// Print guild name
		cout << "[Guild] " << m_guildName << endl;
		
		// Print each character
		for (size_t i = 0; i < m_numCharacter; i++)
		{
			cout << "    " << i + 1 << ": " << *m_character[i] << endl;
		}
	}






}
