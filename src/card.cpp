#include <cstdlib>
#include <iostream>
#include "Card.h"
#include "Hand.h"

Card::Card() : value(determineFace()), suit(determineSuit()) {}; //In C++, objects must be fully constructed the moment they exist — there's no "null object" state for a CardValue.
Card::Card(const std::string& face, Suit s) : value(face), suit(s) {}

Suit Card::determineSuit(){
	int randomNumber = rand() % 4;
	return static_cast<Suit>(randomNumber);
}
std::string Card::determineFace() {
	const std::string faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	return faces[rand() % 13];
}
std::string Card::toString() const{
	return value.getFace() + " of " + suitToString(suit);
}
CardValue Card::getCardValue() const{
	return value;
}
bool Card::isIn(const Hand& sampleHand) const{
	for(const Card& c : sampleHand.getCards()){
		if(equals(c)){
			return true;
		}
	}
	return false;
}
bool Card::equals(const Card& c) const {
	return this->suit == c.suit && this->value.getFace() == c.value.getFace();
 }
// int main(int argc, char* argv[]){
// 	srand(time(0));
// 	// static methods (no instance needed)
// 	std::cout << "Random face: " << Card::determineFace() << std::endl;
// 	std::cout << "Random suit: " << Card::determineSuit() << std::endl;
// 	std::cout << "==========" << std::endl;
// 	// instance methods
// 	Card* alpha = new Card();
// 	std::cout << "full alpha is " << alpha->toString() << std::endl;
// 	std::cout << "alpha's face is " << alpha->getCardValue().getFace() << std::endl;
// 	std::cout << "alpha's numeric is " << alpha->getCardValue().getNumeric() << std::endl;
// 	Card* beta = new Card("J",CLUBS);
// 	std::cout << "beta fully spelled out is " << beta->toString() << std::endl;
// 	std::cout << "is alpha equal to beta? " << alpha->equals(*beta) << std::endl;
// 	Card gamma("7",SPADES);
// 	std::cout << "gamma fully spelled out is " << gamma.toString() << std::endl;
// 	std::cout << "is gamma equal to beta? " << gamma.equals(*beta) << std::endl;
// 	std::cout << "is gamma equal to alpha? " << gamma.equals(*alpha) << std::endl;
// 	Hand* hand1 = new Hand();
// 	hand1->deal(*alpha);
// 	std::cout << "is alpha in hand1? " << alpha->isIn(*hand1) << std::endl;
// 	delete alpha;
// 	delete beta;
// 	delete hand1;
// }