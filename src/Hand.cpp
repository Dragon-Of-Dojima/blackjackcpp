#include <iostream>
#include "Hand.h"

Hand::Hand() {
	this->cardlist = std::vector<Card>();
	this->handValue = Hand::getScore();
 }

 std::string Hand::getHand() const{
	std::string tempString = "[";
	for(int i = 0; i < (int)cardlist.size(); i++){
		if (i > 0) tempString += ", ";
		tempString += cardlist.at(i).toString();
	}
	tempString += "]";
	return tempString;
 }

 int Hand::getSize() const{
	return (int)cardlist.size();
 }
 void Hand::deal(const Card& c){
	cardlist.push_back(c);
 }
 int Hand::getScore(){
	if(isEmpty()){
		return 0;
	}else{
		int sum = 0;
		int aces = 0;
		for(Card& c : cardlist){
			if(c.getCardValue().getFace() == "A"){
				aces++;
			}else{
				sum += c.getCardValue().getNumeric();
			}
		}
		while(aces > 0){
			aces--;
			if(sum <= 10){
				sum += 11;
			}else{
				sum += 1;
			}
		}
		handValue = sum;
		return handValue;
	}
 }
 const std::vector<Card>& Hand::getCards() const{
	return cardlist;
 }
 bool Hand::isEmpty() const{
	return (cardlist.size() == 0);
 }
 int main(int argc, char* argv[]){
	srand(time(0));
	Hand* f = new Hand();
	f->deal(Card());
	f->deal(Card());
	std::cout << "f's hand is " << f->getHand() << std::endl;
	std::cout << "f's score is " << f->getScore() << std::endl;
	delete f;
 }