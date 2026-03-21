#include "Hand.h"
#include "Deck.h"
#include <iostream>
using namespace std;

bool isBusted(const Hand& h){
	return (h.getScore() > 21);
}
int main(int argc, char* argv[]){
	cout << "Welcome to Blackjack!" << endl;
	Deck deck;
	deck.shuffle();
	Hand* playerhand = new Hand();
	Hand* dealerhand = new Hand();
	playerhand->deal(deck.draw());
	dealerhand->deal(deck.draw());
	playerhand->deal(deck.draw());
	dealerhand->deal(deck.draw());
	bool playerStillIn = true;
	while(playerStillIn && (!isBusted(*playerhand))){
		if(playerhand->getScore() != 21){
			cout << "DEALER HAND: " << dealerhand->getHand(true) << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << endl;
			if(playerhand->isSoft()){
				cout << "YOUR SCORE: " << (playerhand->getScore() - 10) << " or " << playerhand->getScore() << endl;
			}else{
				cout << "YOUR SCORE: " << playerhand->getScore() << endl;
			}
			cout << "Hit or stay? Press \"H\" to hit, \"S\" to stay" << endl;
			string choice;
			cin >> choice;
			if(choice == "H" || choice == "h"){
				playerhand->deal(deck.draw());
			}
			else if(choice == "S" || choice == "s"){
				playerStillIn = false;
			}
		}else{
			cout << "DEALER HAND: " << dealerhand->getHand() << endl;
			if (playerhand->getSize() == 2) {
				cout << "BLACKJACK 21! YOU WIN!" << endl;
			} else {
				cout << "21! YOU WIN!" << endl;
			}
			break;
		}
	}
	if(isBusted(*playerhand)){
		cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
		cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
		cout << "BUSTED! YOU LOSE!" << endl;
	}
	else{
		while(dealerhand->getScore() < 17){
			dealerhand->deal(deck.draw());
		}
		if (isBusted(*dealerhand)){
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU WIN!" << endl;
		}
		else if (playerhand->getScore() == dealerhand->getScore()){
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "PUSH" << endl;
		}
		else if (playerhand->getScore() > dealerhand->getScore()){
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU WIN!" << endl;
		}
		else{
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU LOSE!" << endl;
		}
	}
	delete playerhand;
	delete dealerhand;
}