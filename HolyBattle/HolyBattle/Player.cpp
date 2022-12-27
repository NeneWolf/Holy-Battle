#include "Cards.h"
#include "Player.h"

void Player::ResetHealth() {
	health = 20;
}

void Player::loseHealth(int i) {
	//Check if the hit damage is higher then 0, if so remove that amount, if its less or equal to 0, set health instantly to 0;
	health = health - i > 0 ? health - i : 0;
}

bool Player::drawCard() {
	//checks if the player is able to draw a card
	if (deck.size() != 0) {

		//adds the first of the deck into the player hand
		hand.push_back(deck[0]);

		//Removes from the "deck"
		deck.erase(deck.begin());
		return true;
	}
	else
		return false;
}

void Player::playCard(Card* c) {
	cout << "Card played: " << *c << endl;

	// Remove from the hand and add it to the discarded
	discard.push_back(c);

	//Removes from the "hand"
	hand.erase(hand.begin() + cardID);

	//Card effect on after being removed from the hand and added to the discarded
	c->effect(opponent);
}

void Player::myTurn()
{
	endturn = false;
	while (endturn == false && hand.size() > 4)
	{
		cout << "What card would you like to play? (To terminate your turn please enter 9 )\nPs: Any other number will terminate your turn  \n" << endl;

		for (int i = 0; i < hand.size(); i++) {
			cout << i << "- Name: " << hand[i]->getName() << '\n' << " Hit Points: " << hand[i]->getHitPoints() << '\n' << " Description: " << hand[i]->getDescription() << endl;
		}

		cout << "\nCard to play: ";  cin >> cardID; cout << endl;

		//Checks the player input. As long as the player does not select 9 the turn will keep going.
		if (cardID == 9 || cardID <0 || cardID > hand.size()) {
			endturn = true;
			cout << "Your turn ended..." << endl;
		}
		else
			playCard(hand[cardID]);

		//Print information
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 7);
		cout << "\n------\n" << getName() << " Health: " << getHealth() << endl;
		cout << getOpponent()->getName() << " Health: " << opponent->getHealth() << "\n------\n" << endl;
		SetConsoleTextAttribute(h, 3);
	};
}

void Player::dealCards(int numCard) {
	for (int c = 0; c < numCard; c++) {
		//pushes from the main deck "deck" to the second deck "Hand"
		hand.push_back(deck[0]);
		//Removes from the "deck"
		deck.erase(deck.begin());
	}
}

bool Player::hasLost() {
	//If player health is 0, set to true ( has lost ) else its false
	if (health == 0)
		return true;
	else
		return false;

}

int Player::setHealth(int h) { return health = h; }

int Player::getHealth() { return health; }

string Player::setName(string n) { return name = n; }

string Player::getName() { return name; }

void Player::setDeck(vector<Card*> const& de) { deck.assign(de.begin(), de.end()); }

void Player::setHand(vector<Card*> const& han) { hand.assign(han.begin(), han.end()); }

void Player::setDiscard(vector<Card*> const& disc) { discard.assign(disc.begin(), disc.end()); }

Player* Player::setOpponent(Player* p) { return opponent = p; }

HumanPlayer::HumanPlayer()
{
	name = "Player";
	health = 20;
}

ComputerPlayer::ComputerPlayer()
{
	name = "AI Player";
	health = 20;
}

void ComputerPlayer::myTurn()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "AI choose to play ...\n" << endl;

	while (hand.size() > 4) {
		SetConsoleTextAttribute(h, 4);
		cardID = rand() % hand.size();
		playCard(hand[cardID]);

		//Print information

		SetConsoleTextAttribute(h, 7);
		cout << "\n------\n" << getName() << " Health: " << getHealth() << endl;
		cout << getOpponent()->getName() << " Health: " << opponent->getHealth() << "\n------\n" << endl;

	}

	SetConsoleTextAttribute(h, 3);
}
