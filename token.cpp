#include "token.h"
#include <string>
#include <sstream>
#include <iostream>

Token::Token(TokenType type, const std::string& value)
	: type(type), value(value) {}

TokenType Token::getType() const {
	return type;
}

std::string Token::getValue() const {
	return value;
}

void Token::displaySelf() const {
	std::stringstream ss;
	ss << type << ", " << value;

	std::string self = ss.str();
	std::cout << self << std::endl;
}
