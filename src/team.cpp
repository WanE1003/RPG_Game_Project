/***********************************************************************
// File: team.cpp
// Date: Oct 9,2024
// Author: Seungwan Hong
// Email: mambo9991@gmail.com
***********************************************************************/

#include <iostream>
#include <iomanip>
#include "team.h"

using namespace std;

namespace seneca {

	// Constructor
	Team::Team(const char* name) : m_teamName(name), m_numCharacter(0)
	{
		m_capacity = 2;  // Default capacity
		m_character = new Character * [m_capacity];
	}

	// Destructor
	Team::~Team()
	{
		for (size_t i = 0; i < m_numCharacter; i++)
		{
			delete m_character[i];
			m_character[i] = nullptr;
		}
		delete[] m_character;
		m_character = nullptr;
	}

	// Copy Constructor
	Team::Team(const Team& other) : m_teamName{}, m_character {}, m_numCharacter{}, m_capacity{}
	{
		// call copy assignment operator
		*this = other;
	}

	// Copy Assignment Operator
	Team& Team::operator=(const Team& other) 
	{
		if (this != &other)
		{	
			// clean all objects
			for (size_t i = 0; i < m_numCharacter; i++)
			{
				delete m_character[i];
			}
			delete[] m_character;
			// copy resources
			m_teamName = other.m_teamName;
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
	Team::Team(Team&& other) noexcept : m_teamName{}, m_character{}, m_numCharacter{}, m_capacity{} 
	{
		// call move assignment operator
		*this = std::move(other);
	}

	// Move Assignment Operator
	Team& Team::operator=(Team&& other) noexcept 
	{
		if (this != &other)
		{
			// clean up resources
			for (size_t i = 0; i < m_numCharacter; i++)
			{
				delete m_character[i]; 
			}
			// Deallocate the entire character array memory
			delete[] m_character;

			// move resources
			m_teamName = move(other.m_teamName);
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

	// Function that adds the character received as parameter to the team ONLY IF the team doesn't have a character with the same name.
	void Team::addMember(const Character* c)
	{
		// test wether team have a character with the same name.
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

		// Add new character
		m_character[m_numCharacter] = c->clone();

		// Add number of character
		++m_numCharacter;

	}

	// Function that searches the team for a character with the name received as parameter and removes it from the team.
	void Team::removeMember(const std::string& c)
	{
		for (size_t i = 0; i < m_numCharacter; i++)
		{	
			// find character with same name
			if (m_character[i]->getName() == c)
			{
				// delete memory
				delete m_character[i];

				// Move the characters behind it to the front
				for (size_t j = i; j < m_numCharacter - 1; j++)
				{
					m_character[j] = m_character[j + 1];
				}

				// Clean memory of last character
				m_character[m_numCharacter - 1] = nullptr;

				// reduce number of character
				--m_numCharacter;

				return;
			}
		}
	}

	//  Funtion that returns the character ar the index specified as parameter, or null if the index is out of bounds.
	Character* Team::operator[](size_t idx) const
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

	// Function that prints to screen the content of current object
	void Team::showMembers() const
	{
		// if team is empty print no team
		if (m_numCharacter == 0)
		{
			cout << "No team." << endl;
			return;
		}

		// print team name
		cout << "[Team] " << m_teamName << endl;

		// print name of character and details
		for (size_t i = 0; i < m_numCharacter; i++)
		{
			cout << "    " << i + 1 << ": " << *m_character[i] << endl;
		}
	}


}
