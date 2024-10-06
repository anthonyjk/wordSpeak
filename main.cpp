#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main() {


	std::ifstream codefile("main.speak");
	std::string str;
	std::string code;
	while (std::getline(codefile, str)) {
		code += str;
		code.push_back('\n');
	}

	//std::cout << code <<std::endl;

	Lexer myLexer(code);

	std::vector<Token> tokens =  myLexer.lex();

	//myLexer.displayTokens();

	Parser myParser(tokens);

	myParser.parse();

	//std::cout << "Displaying tokens:" << std::endl;

	return 0;
}
	
