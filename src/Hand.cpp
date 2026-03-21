#include <iostream>
#include "Hand.h"

Hand::Hand() {
	this->cardlist = std::vector<Card>();
	this->handValue = Hand::getScore();
 }

 std::string Hand::getHand(bool hideHoleCard) const{
	std::string tempString = "[";
	for(int i = 0; i < (int)cardlist.size(); i++){
		if (i > 0) tempString += ", ";
		if(hideHoleCard == true && i == 0){
			tempString += "hidden";
		}else{
			tempString += cardlist.at(i).toString();
		}
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
 std::pair<int, bool> Hand::computeScore() const{
	if(isEmpty()) return {0, false};
	int sum = 0;
	int aces = 0;
	for (const Card& c : cardlist) {
		sum += c.getCardValue().getNumeric();
		if (c.getCardValue().getFace() == "A") aces++;
	}
	while (sum > 21 && aces > 0) {
		sum -= 10;
		aces--;
	}
	return {sum, aces > 0};
 }
 int Hand::getScore() const{
	return computeScore().first;
 }
 bool Hand::isSoft() const{
	return computeScore().second;
 }
 const std::vector<Card>& Hand::getCards() const{
	return cardlist;
 }
 bool Hand::isEmpty() const{
	return (cardlist.size() == 0);
 }