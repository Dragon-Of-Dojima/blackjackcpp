#include "CardValue.h"
//#include <iostream>
CardValue::CardValue(const std::string& faceval){
	this->face = faceval;
	this->numeric = findNumericVal(faceval); //faceval is already the string itself (thanks to the reference)
}

int CardValue::findNumericVal(const std::string& f){
	if(f == "A"){
		return 11;
	}
	else if(f == "J" || f == "Q" || f == "K"){
		return 10;
	}
	else{
		return std::stoi(f);
	}
}

std::string CardValue::getFace() const{
	return this->face;
}

int CardValue::getNumeric() const{
	return this->numeric;
}
// int main(){
// 	//can do this like, which allocates on the heap
// 	// CardValue* c = new CardValue("K"); 
// 	// std::cout << c->getNumeric() << std::endl;
// 	// std::cout << c->getFace() << std::endl;
// 	// delete c

// 	//Stack allocation in C++ is prefered
// 	CardValue c("K");
// 	std::cout << c.getNumeric() << std::endl;
// 	std::cout << c.getFace() << std::endl;
// }