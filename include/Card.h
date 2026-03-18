#pragma once
#include "CardValue.h"
#include "Suit.h"
#include <string>
class Hand;  // forward declaration — avoids needing to include Hand.h
class Card{
	CardValue value;
	Suit suit;
	public:
		Card();
		static Suit determineSuit();
		static std::string determineFace();
		std::string toString() const;
		CardValue getCardValue() const;
		bool isIn(const Hand& sampleHand) const;
		bool equals(const Card& c) const;
};