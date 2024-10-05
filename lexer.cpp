#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "token.h"

Lexer::Lexer(const std::string& code) : code(code), pointer(0), tokens({}) {
}

void Lexer::displayCode() const {
	std::cout << code << std::endl;
}

void Lexer::displayTokens() const {
	for(const auto& token : tokens)
	{
		token.displaySelf();
	}
}

std::vector<Token> Lexer::lex() {
	while(pointer < code.length()) {
		std::cout << code[pointer] << std::endl;
		tokens.push_back(getNextToken());
	}
	tokens.push_back(Token(TokenType::TOKEN_EOF, "EOF"));

	return tokens;
}

void Lexer::advance() {
	pointer++;
}

void Lexer::skipEmpty() {
	while(code[pointer] == ' ') {
		pointer++;
	}
}

Token Lexer::getNextToken() {

	if (code[pointer] == ' ') {
		skipEmpty();
	}

	if(code.substr(pointer, 3) == "say") {
		pointer += 3;
		return Token(TokenType::TOKEN_SAY, "say");
	} else if (code.substr(pointer, 5) == "words") {
		pointer += 6; // skip 'words '
		return Token(TokenType::TOKEN_STRING, collectString());
	} else if (code.substr(pointer, 4) == "give") {
		pointer += 5;
		return Token(TokenType::TOKEN_ID, getSymbol());
	} else if (code.substr(pointer, 2) == "as") {
		pointer += 2;
		return Token(TokenType::TOKEN_AS, "as");
	} else if (isdigit(code[pointer])) { //only works for positive ints at the moment
		return Token(TokenType::TOKEN_INTEGER, getInteger());
	} else if (code.substr(pointer, 1) == "\n") {
		pointer += 1;
		return Token(TokenType::TOKEN_NEWLINE, "\n");
	}
	else {
		return Token(TokenType::TOKEN_ID, getIdentifier()); // TODO: Figure out why this gives a crazy result
	}
	advance();
}

std::string Lexer::getIdentifier() {
	std::string readID = "";
	while(pointer < code.length() && code[pointer] != ' ') {
		std::cout << code[pointer] << std::endl;
		readID += code[pointer];
		advance();
	}

	return readID;
}

std::string Lexer::getInteger() {
	std::string readInt = "";

	while(pointer < code.length() && isdigit(code[pointer])) {
		readInt += code[pointer];
		advance();
	}

	return readInt;
}

std::string Lexer::getSymbol() {
	std::string readSymbol = "";
	while(pointer < code.length() && code[pointer] != ' ') {
		readSymbol += code[pointer];
		advance();
	}

	return readSymbol;
}

std::string Lexer::collectString() {
	std::string readString = "";
	while(code.substr(pointer, 8) != "endwords")
	{
		readString += code[pointer];
		advance();
	}
	pointer += 8;
	return readString;
}


