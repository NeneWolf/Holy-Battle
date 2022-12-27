#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class Player;

///////////////// Card Class
class Card {
public:

	Card() {}

	//virtual ~Card();

	//Get name from the sub-class and Set the name of the card
	virtual string setName(string n);
	virtual string getName();

	//Get name from the sub-class and Set the description of the card
	virtual string setDescription(string d);
	virtual string getDescription();

	//Get Hit Points from the sub-class and Set the name of the card
	virtual int setHitPoints(int h) { return hitPoints = h; }
	virtual int getHitPoints() { return hitPoints; }

	//Get Number of Cards in the deck from the sub-class and Set the name of the card
	virtual int setNCards(int c) { return numberOfCards = c; }
	virtual int getNumberOfCards() { return this->numberOfCards; }

	virtual void effect(Player* p) = 0;

	friend ostream& operator<<(ostream& output, const Card& c) {
		output << c.name << "(" << c.hitPoints << ")";
		return output;
	}

private:
	string name;
	int hitPoints;
	int numberOfCards;
	string description;
};

/////////////////SubClass of Cards
class Painful : public Card
{
public:
	Painful() {}
	virtual void effect(Player* p);

private:
	string name = setName("Painful");
	int hitPoints = setHitPoints(2);
	int numberOfCards = setNCards(5);
	string description = setDescription("Opponent loses 2 health and draws a card.");
};

class Spite : public Card
{
public:
	Spite() {}
	virtual void effect(Player* p);
private:
	string name = setName("Spite");
	int hitPoints = setHitPoints(1);
	int numberOfCards = setNCards(6);
	string description = setDescription("Both players lose 1 health.");
};

class fHeal : public Card
{
public:
	fHeal() {}
	virtual void effect(Player* p);
private:
	string name = setName("Full Heal");
	int hitPoints = setHitPoints(0);
	int numberOfCards = setNCards(1);
	string description = setDescription("Restores your health back to 20.");
};

class Switch : public Card
{
public:
	Switch() {}
	virtual void effect(Player* p);
private:
	string name = setName("Switcheroo");
	int hitPoints = setHitPoints(0);
	int numberOfCards = setNCards(2);
	string description = setDescription("Swaps the contents of your hand with your opponent's");
};

class Refresh : public Card
{
public:
	Refresh() {}
	virtual void effect(Player* p);
private:
	string name = setName("Refresh");
	int hitPoints = setHitPoints(3);
	int numberOfCards = setNCards(2);
	string description = setDescription("Lose 3 health and shuffle your discard pile back into your deck.");
};

class Peek : public Card
{
public:
	Peek() {}
	virtual void effect(Player* p);
private:
	string name = setName("Peek");
	int hitPoints = setHitPoints(0);
	int numberOfCards = setNCards(4);
	string description = setDescription("Look at the top cards of both player's decks.");
};