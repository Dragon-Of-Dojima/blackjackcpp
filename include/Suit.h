#pragma once
#include <string>
enum Suit{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

inline std::string suitToString(Suit s){
	const std::string names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	return names[s];
}