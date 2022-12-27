#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Player.h"
#include <windows.h>

using namespace std;

void print(vector<Card*> cards);
bool CheckHealth(vector<Player*> players);
void Introduction();
void Restart();


///////////////// Class that holds all the functionalities of the game
class Game {
public:
	bool playerAI;
	int numberOfPlayer;
	int numberOfCardsPerHand;

	Game() : playerAI(true), numberOfPlayer(2), numberOfCardsPerHand(5) {}

	vector<Player*> players;

	// Creates the "players" and provides them with their cards
	void initializeGame() {

		cout << "Creating player and AI..." << endl;
		players.push_back(new HumanPlayer());
		players.push_back(new ComputerPlayer());

		cout << "Giving cards to both players...\n" << endl;

		//Create, Assign and distribute to each player their respective hands
		for (int i = 0; i < players.size(); i++) {
			//Give player the hand cards
			players[i]->dealCards(numberOfCardsPerHand);
		};

	};

	// Function that holds the turns between the player and the AI
	void play() {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Along the code, this line allows the system to chance the text color.

		cout << "\n============ Game Starting ============\n" << endl;

		bool gameOver = false; // bool that determines when the game has ended

		//Set opponents 
		players[0]->setOpponent(players[1]);
		players[1]->setOpponent(players[0]);

		while (gameOver != true) {

			////////////////////Player Round

			SetConsoleTextAttribute(h, 3); // Changes the color of the text ( appears multiple times along the code )

			if (players[0]->drawCard()) {
				cout << "Player has drawn one card." << endl;
			}
			else
				cout << "Deck empty... No card was taken" << endl;

			cout << "Player Turn...\n" << endl;
			players[0]->myTurn();

			gameOver = CheckHealth(players); // Checks at the end of each turn if any of the players have died

			if(gameOver == true)
				break;


			 
			////////////////////AI Round

			SetConsoleTextAttribute(h, 4);

			cout << "AI Turn...\n" << endl;

			if (players[1]->drawCard()) {
				cout << "AI has taken 1 card." << endl;
			}
			else
				cout << "AI couldn't take any card" << endl;

			players[1]->myTurn();

			gameOver = CheckHealth(players);

			if (gameOver == true)
				break;
		}

		SetConsoleTextAttribute(h, 6);

		if (players[0]->getHealth() == 0)
			cout << "\n============ AI won the game >:) ============\n " << endl;
		else if (players[1]->getHealth() == 0)
			cout << "\n============ You have won the game!! ============\n" << endl;

		//Restarts the game
		Restart();
	};
};

int main() {

	Introduction();
}

// Checks the players health
bool CheckHealth(vector<Player*> players) {
	if (players[0]->getHealth() != 0 && players[1]->getHealth() != 0) {
		return false;
	}
	else
		return true;
}

// Provides the player with the starting information
void Introduction() {

	char answer;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);

	cout << "------- Welcome to Holy Battle -------" << endl;
	cout << "Please enter P to start the game or R to view the rules." << endl;

	cin >> answer;
	
	while (!((answer == 'R') ||(answer == 'P')||(answer == 'r') || (answer == 'p'))) {
		cin >> answer;
	}

	if (answer == 'R' || answer == 'r') {
		cout << "\n-------" << endl;
		cout << "Holy Battle is a card base game. \nEach turn the player will receive 1 card. \nThe player is able to play as many cards as you can as long as in your hand there is no less then 5 cards. " << endl;
		cout << "The main objective of the game is to kill the opponent. \nHaving no cards in the deck or health reaching 0 HP is a Game Over." << endl;
		cout << "\n \n" << endl;
		Introduction();
	}
	else if(answer == 'P' || answer == 'p') {
		Game newGame;
		newGame.initializeGame();
		newGame.play();
	}
}

//Restarts the hole game 
void Restart() {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);

	char answer;

	cout << "Would you like to restart the game ? (Y / N) " << endl;

	cin >> answer;

	while (!((answer == 'Y') || (answer == 'y') || (answer == 'N') || (answer == 'n'))) {
		cin >> answer;
	}

	if (answer == 'Y' || answer == 'y') {
		Introduction();
	}
	else {
		SetConsoleTextAttribute(h, 6);
		cout << "Thank you for playing 'Holy Battle'.\nMade by: Ines Mateus Lobo\nFind more games at https://ineslobo.co.uk/ "<<endl;
	}
}
