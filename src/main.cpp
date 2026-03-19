#include <cstdlib>
#include <ctime>
#include "Card.h"
#include "Hand.h"
#include <iostream>
using namespace std;

void dealIn(Hand& h){
    
	Card* a = new Card();
	Card* b = new Card();
	
	h.deal(*a);
	
	while(h.getSize() < 2){
	  if(!b->isIn(h)){
			h.deal(*b);
		}
		else dealIn(h);
	}
	delete a;
	delete b;
	return;
}

void hit(Hand& a, const Hand& b){
	while(true){
		Card c;
		if(!c.isIn(a) && !c.isIn(b)){
			a.deal(c);
			return;
		}
	}
}
bool isBusted(const Hand& h){
	return (h.getScore() > 21);
}
bool notBusted(const Hand& player, const Hand& dealer){
	return((!isBusted(player)) && (!isBusted(dealer))); 
}
int main(int argc, char* argv[]){
	srand(time(0));
	cout << "Welcome to Blackjack!" << endl;
	Hand* playerhand = new Hand();
	Hand* dealerhand = new Hand();
	dealIn(*playerhand);
	hit(*dealerhand,*playerhand);
	hit(*dealerhand,*playerhand);
	cout << "DEALER HAND: " << dealerhand->getHand() << endl;
	cout << "YOUR HAND: " << playerhand->getHand() << endl;
	bool playerStillIn = true;
	while(playerStillIn && (!isBusted(*playerhand))){
		if(playerhand->getScore() != 21){
			cout << "Hit or stay? Press \"H\" to hit, \"S\" to stay" << endl;
			string choice;
			cin >> choice;
			if(choice == "H" || choice == "h"){
				hit(*playerhand,*dealerhand);
				cout << "YOUR HAND: " << playerhand->getHand() << endl;
				cout << "YOUR SCORE: " << playerhand->getScore() << endl; 
			}
			else if(choice == "S" || choice == "s"){
				playerStillIn = false;
			}
		}else{
			cout << "BLACKJACK 21! YOU WIN!" << endl;
			break;
		}
	}
	if(isBusted(*playerhand)){
		cout << "BUSTED! YOU LOSE!" << endl;
	}
	else{
		while(((dealerhand->getScore() < 17) && (notBusted(*playerhand,*dealerhand))) && (playerhand->getScore() != 21)){
			hit(*dealerhand,*playerhand);
		}
		if ((playerhand->getScore() == dealerhand->getScore())) {
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;;
			cout << "PUSH" << endl;
		}
		
		else if((isBusted(*dealerhand)) && (playerhand->getScore() != 21)){
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU WIN!" << endl;
		}
	
		else if ((playerhand->getScore() < dealerhand->getScore())) {
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU LOSE!" << endl;
		}
		
		else if ((playerhand->getScore() > dealerhand->getScore()) && playerhand->getScore() != 21)  {
			cout << "DEALER HAND: " << dealerhand->getHand() << " and SCORE: " << dealerhand->getScore() << endl;
			cout << "YOUR HAND: " << playerhand->getHand() << " and SCORE: " << playerhand->getScore() << endl;
			cout << "YOU WIN!" << endl;
		}
	}
	delete playerhand;
	delete dealerhand;
}