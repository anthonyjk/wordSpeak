#include "lexer.h"
#include <iostream>
#include <string>

int main() {

	std::string code = "give y as 10\nsay words this is a string endwords";
	Lexer myLexer(code);

	myLexer.lex();

	std::cout << "Displaying tokens:" << std::endl;
	myLexer.displayTokens();

	return 0;
}
	
