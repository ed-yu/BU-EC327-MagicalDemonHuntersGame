# BU-EC327-MagicalDemonHuntersGame

*C++ program for solving problems relating to User-Defined Types, Encapsulation, Operator Overloading, Interacting Objects, Dynamic Allocation, Program Organization, Exceptions, Save/Load, and STL. Developed as part of EC327: Introduction to Software Engineering at Boston University.*

## Program Overview

A C++ program that is implemented with a "simulation" that involves "mage vs demon battles" consisting of objects located in a two-dimensional world that move around and behave in various ways. The user enters commands to direct actions to objects, and they behave in simulated time. Simulated time advances one "tick" or unit at a time. Time is "frozen" while the user enters commands. The user commands the program to advance one tick of time or "run" the program in which the time will advance several units of time until a significant event is triggered.

*You command mages. You are trying to defeat the demons in Demon Hideouts but you need to have enough mana to do it. You must find demons and earn experience by battling. However, you also need to periodically get crystals to stay alive. You "win" the game by defeating all the demons without losing all your mana.*

## Class Breakdown

Point2D - represents a point on a Cartesian coordinate system.

Vector2D - represents a vector in the real plane.

GameObject - base class for all objects in the game.

Building - base class for all building objects in the game.

ManaSpire - The ManaSpire is used to recover mana but they have a limit on usage. Inherits various member variables from Building.
DemonHideout - location for demons to battle. "Experience" is gained by completing battles. Inherits various member variables from Building.

RoamingDemon - Roaming Demons are on the game board and if a Mage comes "into contact" with them, the Mage loses health. The Mage can use its mana to defeat the Roaming Demon.

AncientDemon - A more "evolved" form of Roaming Demon with increased health and attack. If a Mage comes into contact with an Ancient Demon, a Curse state is bounded to the Mage and it takes 2X the amount of mana per health to defeat the AncientDemon. Once defeated, the respective Mage is awarded with 50 mana.

Mage - a simulated player object which has three abilities:
  - Move to a specified location
  - Recover mana from a specific ManaSpire
  - Gain experience from a specific DemonHideout

View - Displays game objects.

Model - Holds references to game objects.

GameCommand - Handles commands from user input.
