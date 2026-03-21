#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Card.h"
class Hand{
	std::vector<Card> cardlist;
	int handValue;
	std::pair<int, bool> computeScore() const;
	public:
		Hand();
		std::string getHand(bool hideHoleCard = false) const;
		int getSize() const;
		void deal(const Card& c);
		int getScore() const;
		bool isSoft() const;
		bool isEmpty() const;
		const std::vector<Card>& getCards() const;
};