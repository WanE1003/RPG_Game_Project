# RPG Game Project - C++, OOP and Templates
This project is a simplified RPG (Role-Playing Game) simulation developed in C++ as part of an advanced programming workshop. It demonstrates key Object-Oriented Programming (OOP) principles, template programming, memory management practices, and design patterns in C++17. The game features various character classes, including Barbarian, Archer, and Rogue, each designed with unique health, attack, defense, weapon, and ability configurations. By leveraging templates, the project allows for flexible and reusable code structures, ensuring adaptability for different gameplay mechanics.

## Features
* **Character Templates:** A templated `CharacterTpl` class manages character health and damage calculations, supporting fundamental and custom health types like `SuperHealth`.
* **Specialized Classes:** Derived classes for each character type:
  * **Barbarian** Focused on melee combat with strong defensive skills.
  * **Archer** Utilizes ranged attacks with defense multipliers.
  * **Rogue** Equipped with dual special abilities and enhanced attack tactics..
* **Memory Management:** All code is compiled with debugging symbols and optimized for Valgrind to identify potential memory leaks.
* **Combat System:** Each character has a unique attack method, managing abilities and weapon stats to deal variable damage to enemies.
* **Error Handling and Testing:** Command-line testing using diff and Valgrind for debugging.

## Tech Stack
* Language: C++17
* Tools: GCC 10.2.0, Valgrind, Git
* Design Patterns: Template-based inheritance, Encapsulation, Modular Design
