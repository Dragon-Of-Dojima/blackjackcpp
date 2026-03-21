#pragma once
#include <string>
class CardValue{
	std::string face;
	int numeric;
	public:
		CardValue(const std::string& faceVal);
		std::string getFace() const;
		int getNumeric() const;
		static int findNumericVal(const std::string& f);
};