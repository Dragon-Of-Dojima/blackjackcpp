#include "Game.h"
#include <iostream>

Game::Game() : status(WAITING) {} //initializer list

void Game::deal(){
	deck = Deck();
	deck.shuffle();
	playerHand = Hand();
	dealerHand = Hand();
	playerHand.deal(deck.draw());
	dealerHand.deal(deck.draw());
	playerHand.deal(deck.draw());
	dealerHand.deal(deck.draw());

	if(playerHand.getScore() == 21){
		status = PLAYER_BLACKJACK;
	}else{
		status = PLAYER_TURN;
	}
}

void Game::hit(){
	if(status != PLAYER_TURN) return;

	playerHand.deal(deck.draw());

	if(playerHand.getScore() > 21){
		status = PLAYER_BUST;
	}else if(playerHand.getScore() == 21){
		status = PLAYER_21;
	}
}

void Game::stay(){
	if(status != PLAYER_TURN && status != PLAYER_21) return;
	resolveStay();
}

void Game::resolveStay(){
	while(dealerHand.getScore() < 17){
		dealerHand.deal(deck.draw());
	}

	if(dealerHand.getScore() > 21){
		status = DEALER_BUST;
	}else if(playerHand.getScore() == dealerHand.getScore()){
		status = PUSH;
	}else if(playerHand.getScore() > dealerHand.getScore()){
		status = PLAYER_WIN;
	}else{
		status = DEALER_WIN;
	}
}

GameStatus Game::getStatus() const{
	return status;
}

const Hand& Game::getPlayerHand() const{
	return playerHand;
}

const Hand& Game::getDealerHand() const{
	return dealerHand;
}

std::string Game::statusToString() const{
	switch(status){
		case WAITING: return "waiting";
		case PLAYER_TURN: return "player_turn";
		case PLAYER_BUST: return "player_bust";
		case PLAYER_BLACKJACK: return "player_blackjack";
		case PLAYER_21: return "player_21";
		case DEALER_BUST: return "dealer_bust";
		case PLAYER_WIN: return "player_win";
		case DEALER_WIN: return "dealer_win";
		case PUSH: return "push";
		default: return "unknown";
	}
}
