#include "token.h"
#include <string>

Token::Token(TokenType type, const std::string& value)
	: type(type), value(value) {}

TokenType Token::getType() const {
	return type;
}

std::string Token::getValue() const {
	return value;
}
