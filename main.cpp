#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <iostream>
#include <string>
#include <vector>

int main() {

	std::string code = "give y as 10\nsay y";
	std::string test = "say y";
	Lexer myLexer(code);

	std::vector<Token> tokens =  myLexer.lex();

	Parser myParser(tokens);

	myParser.parse();

	//std::cout << "Displaying tokens:" << std::endl;
	//myLexer.displayTokens();

	return 0;
}
	
