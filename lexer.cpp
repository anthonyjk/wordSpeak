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

void Lexer::skipLine() {
	while(code[pointer] != '\n' && pointer < code.length()) {
		pointer++;
	}
}

Token Lexer::getNextToken() {

	if (code[pointer] == ' ') {
		skipEmpty();
	}

	if (isalnum(code[pointer]) == false) {
		skipLine(); // fix this
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
	} else if (code.substr(pointer, 4) == "plus") {
		pointer += 4;
		return Token(TokenType::TOKEN_PLUS, "plus");
	} else if (code.substr(pointer, 5) == "minus") {
		pointer += 5;
		return Token(TokenType::TOKEN_MINUS, "minus");
	} else if (code.substr(pointer, 5) == "while") {
		pointer += 5;
		return Token(TokenType::TOKEN_WHILE, "while");
	} else if (code.substr(pointer, 2) == "if") {
		pointer += 2;
		return Token(TokenType::TOKEN_IF, "if");
	} else if (code.substr(pointer, 4) == "else") {
		pointer += 4;
		return Token(TokenType::TOKEN_ELSE, "else");
	} else if (code.substr(pointer, 4) == "same") {
		pointer += 4;
		return Token(TokenType::TOKEN_SAME, "same");
	} else if (code.substr(pointer, 2) == "or") {
		pointer += 2;
		return Token(TokenType::TOKEN_OR, "or");
	} else if (code.substr(pointer, 3) == "and") {
		pointer += 3;
		return Token(TokenType::TOKEN_AND, "and");
	} else if (code.substr(pointer, 4) == "more") {
		pointer += 4;
		return Token(TokenType::TOKEN_MORE, "more");
	} else if (code.substr(pointer, 4) == "less") {
		pointer += 4;
		return Token(TokenType::TOKEN_LESS, "less");
	} else if (code.substr(pointer, 3) == "not") {
		pointer += 3;
		return Token(TokenType::TOKEN_NOT, "not");
	} else if (code.substr(pointer, 4) == "open") {
		pointer += 4;
		return Token(TokenType::TOKEN_OPEN, "open");
	} else if (code.substr(pointer, 5) == "close") {
		pointer += 5;
		return Token(TokenType::TOKEN_CLOSE, "close");
	}
	else {
		return Token(TokenType::TOKEN_ID, getIdentifier());
	}
	advance();
}

std::string Lexer::getIdentifier() {
	std::string readID = "";
	while(pointer < code.length() && code[pointer] != ' ' && code[pointer] != '\n') {
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
	while(pointer < code.length() && code[pointer] != ' ' && code[pointer != '\n']) {
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


