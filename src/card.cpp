#include <cstdlib>
#include <iostream>
#include "Card.h"

Card::Card() : value(determineFace()), suit(determineSuit()) {}; //In C++, objects must be fully constructed the moment they exist — there's no "null object" state for a CardValue.

Suit Card::determineSuit(){
	int randomNumber = rand() % 4;
	return static_cast<Suit>(randomNumber);
}
std::string Card::determineFace() {
	const std::string faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	return faces[rand() % 13];
}
std::string Card::toString() const{
	return value.getFace() + " of " + std::to_string(suit);
}
CardValue Card::getCardValue() const{
	return value;
}
// bool isIn(const Hand& sampleHand) const{
// 	int acc = 0;
// 	for(Card& c : sampleHand.cardlist){
// 		if(!equals(c)){
// 			acc++;
// 		}
// 	}
// 	return (sampleHand.size() - 1);
// }
// bool equals(const Card& c) const{
// 	return(((this.value.numeric == c.value.numeric) && (this.suit.equals(c.suit))) && (this.value.face == c.value.face));
// }
int main(int argc, char* argv[]){
	srand(time(0));
	    // static methods (no instance needed)
	    std::cout << "Random face: " << Card::determineFace() << std::endl;
	    std::cout << "Random suit: " << Card::determineSuit() << std::endl;
	    // instance methods
	    Card* alpha = new Card();
	    std::cout << alpha->toString() << std::endl;
	    std::cout << alpha->getCardValue().getFace() << std::endl;
	    std::cout << alpha->getCardValue().getNumeric() << std::endl;
}