#include "Card.h"

Card::Card(const std::string& face, Suit s) : value(face), suit(s) {}

std::string Card::toString() const{
	return value.getFace() + " of " + suitToString(suit);
}
CardValue Card::getCardValue() const{
	return value;
}