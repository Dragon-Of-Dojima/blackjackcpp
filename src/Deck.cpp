#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>

Deck::Deck() {
	const std::string faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	for (int s = 0; s < 4; s++) {
		for (int f = 0; f < 13; f++) {
			cards.push_back(Card(faces[f], static_cast<Suit>(s)));
		}
	}
	// for(const Card& thecard : cards){
	// 	std::cout << thecard.toString() << std::endl;
	// }
}

void Deck::shuffle(){
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards.begin(),cards.end(),g);
	// for(const Card& thecard : cards){
	// 	std::cout << thecard.toString() << std::endl;
	// }
}
Card Deck::draw(){
	Card cardToRet = cards.back();
	cards.pop_back();
	return cardToRet;
}
int Deck::remaining() const{
	return cards.size();
}

// int main(int argc, char* argv[]){
// 	Deck d;
// 	d.shuffle();
// 	d.draw();
// 	int num = d.remaining();
// 	std::cout << num << std::endl;
// }