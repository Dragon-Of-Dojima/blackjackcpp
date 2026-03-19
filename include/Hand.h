#pragma once
#include <vector>
#include <string>
#include "Card.h"
//class Card; forward declaration (class Card;) trick we used in Card.h for Hand& doesn't work here because std::vector<Card> needs the full class definition to know how big a Card is. Forward declarations only work when you're using references or pointers to a type.
class Hand{
	std::vector<Card> cardlist;
	int handValue;
	public:
		Hand();
		std::string getHand() const;
		int getSize() const;
		void deal(const Card& c);
		int getScore() const;
		bool isEmpty() const;
		const std::vector<Card>& getCards() const;
};