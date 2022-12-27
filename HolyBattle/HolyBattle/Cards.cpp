#include "Cards.h"
#include "Player.h"

string Card::setName(string n)
{
	return name = n;
}

string Card::getName()
{
	return name;
}

string Card::setDescription(string d)
{
	return description = d;
}

string Card::getDescription()
{
	return description;
}

void Painful::effect(Player* p) {
	p->loseHealth(hitPoints);
	p->drawCard();
}

void Spite::effect(Player* p) {
	p->loseHealth(hitPoints);
	p->getOpponent()->loseHealth(hitPoints);
}

void fHeal::effect(Player* p) {
	p->getOpponent()->ResetHealth();
}

void Switch::effect(Player* p) {
	vector<Card*> temp;
	temp = p->getHand();
	p->setHand(p->getOpponent()->getHand());
	p->getOpponent()->setHand(temp);
}

void Refresh::effect(Player* p) {
	//p is the opponent
	p->getOpponent()->loseHealth(hitPoints);

	vector<Card*> temp;
	temp = p->getOpponent()->getDeck();

	for (int i = 0; i < p->getOpponent()->getDiscard().size(); i++) {
		temp.push_back(p->getOpponent()->getDiscard().at(i));
	}

	p->getOpponent()->setDeck(temp);
	temp.clear();
	p->getOpponent()->setDiscard(temp);

}

void Peek::effect(Player* p) {

	cout << "Cards in the "<< p->getName() <<" deck :\n";
	cout << "------------\n" << endl;

	for (int i = 0; i < 3; i++) {
		cout << i << "- Name: " << p->getDeck()[i]->getName() << endl;
	}
}
