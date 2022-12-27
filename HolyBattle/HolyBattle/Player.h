#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include <windows.h>

using namespace std;

/////////////////Player class
class Player {

public:
	int cardID;
	bool endturn = false;

	Player() {};

	//// Reset health of the "player" to full -> 20
	virtual void ResetHealth();

	//// Lose the given amount of health
	virtual void loseHealth(int i);

	//// Top card from the deck to the hand - Return false if the deck is empty and true if its not
	virtual bool drawCard();

	//// To play a card by removing it from the hand, applying its effect and moving it to the discard pile
	virtual void playCard(Card* c);

	//// To play a game turn
	virtual void myTurn();

	//// Play the card selected
	virtual void dealCards(int numCard);

	////To check if the player has lost  -  Health is 0 or drawCard is false
	virtual bool hasLost();

	//Setting health of the Player & Computer
	virtual int setHealth(int h);
	virtual int getHealth();

	//Set Player Name
	virtual string setName(string n);
	virtual string getName();

	//Get & Set Deck
	virtual void setDeck(vector<Card*> const& de);
	virtual vector<Card*> const& getDeck() const{ return deck; }

	//Get & Set Hand
	virtual void setHand(vector<Card*> const& han);
	virtual vector<Card*> const& getHand() const { return hand; }

	//Get & Set Discard
	virtual void setDiscard(vector<Card*> const& disc);
	virtual vector<Card*> const& getDiscard() const { return discard; }

	//Get & Set opponent
	virtual Player* setOpponent(Player* p);
	virtual Player* const& getOpponent() const { return opponent; }

protected:

	vector<Card*> deck = createDeck();
	vector<Card*> hand;
	vector<Card*> discard;
	string name;
	int health;
	Player* opponent = NULL;
	vector<Card*> createDeck()
	{
		vector<Card*> deck;
		const int maxDeckSize = 20;

		int x = 0;
		int t = 0;
		int y = 0;
		int z = 0;
		int h = 0;
		int w = 0;


		for (int count = 0; count < maxDeckSize; count++) {
			if (x < Painful().getNumberOfCards()) {
				deck.push_back(new Painful());
				x++;
			}

			if (t < Spite().getNumberOfCards()) {
				deck.push_back(new Spite());
				t++;
			}

			if (y < fHeal().getNumberOfCards()) {
				deck.push_back(new fHeal());
				y++;
			}

			if (z < Switch().getNumberOfCards()) {
				deck.push_back(new Switch());
				z++;
			}

			if (h < Refresh().getNumberOfCards()) {
				deck.push_back(new Refresh());
				h++;
			}

			if (w < Peek().getNumberOfCards()) {
				deck.push_back(new Peek());
				w++;
			}

		}

		//Shuffle the cards
		default_random_engine engine;
		engine.seed(std::chrono::system_clock::now().time_since_epoch().count());

		auto rng = default_random_engine{ engine };

		std::shuffle(begin(deck), end(deck), rng);

		return deck;
	}
};

/////////////////SubClass HumanPlayer
class HumanPlayer : public Player {
public:
	HumanPlayer();
};

//////////////////SubClass ComputerPlayer 
class ComputerPlayer : public Player {
public:
	ComputerPlayer();

	virtual void myTurn();
};