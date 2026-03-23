#pragma once
#include "Deck.h"
#include "Hand.h"
#include <string>

enum GameStatus{ //substituing for bools
	WAITING,
	PLAYER_TURN,
	PLAYER_BUST,
	PLAYER_BLACKJACK,
	PLAYER_21,
	DEALER_BUST,
	PLAYER_WIN,
	DEALER_WIN,
	PUSH
};

class Game{
	Deck deck;
	Hand playerHand;
	Hand dealerHand;
	GameStatus status;
	void resolveStay();
	public:
		Game();
		void deal();
		void hit();
		void stay();
		GameStatus getStatus() const;
		const Hand& getPlayerHand() const;
		const Hand& getDealerHand() const;
		std::string statusToString() const;
};
