#include <vector>
#include "Card.h"
class Deck{
	std::vector<Card> cards;
	public:
		Deck();
		void shuffle();
		Card draw();
		int remaining() const;	
};