#pragma once
#include "CardValue.h"
#include "Suit.h"
#include <string>
class Card{
	CardValue value;
	Suit suit;
	public:
		Card(const std::string& face, Suit s);
		std::string toString() const;
		CardValue getCardValue() const;
		Suit getSuit() const;
};