#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "token.h"

class Lexer {
private:
	std::string code;
	int pointer = 0;
	std::vector<Token> tokens;

public:
	Lexer(const std::string& code);

	void displayCode() const;

	void displayTokens() const;

	void lex();

	void advance();

	void skipEmpty();

	Token getNextToken();

	std::string getIdentifier();

	std::string getInteger();

	std::string getSymbol();

	std::string collectString();
	
};

#endif
