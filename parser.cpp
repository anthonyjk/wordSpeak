#include "token.h"
#include "parser.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pointer(0), int_symbols({}), str_symbols({}) {
}

void Parser::advance() {
    pointer++;
}

void Parser::parse() {
    while(pointer < tokens.size()) {
        tokens[pointer].displaySelf();
        if(tokens[pointer].getType() == TOKEN_ID) {
            checkID();
        }
        advance();
    }
}

void Parser::checkID() {
    std::cout << "ID Checked!" << std::endl;
   /* if (int_symbols.count(tokens[pointer]) > 0) {
        // int
    } else if (str_symbols.count(tokens[pointer]) > 0)  {
        // str
    } else {
        Token cur_symbol = tokens[pointer];
        advance();
        if (tokens[pointer].getType == TOKEN_AS) {
            advance();
            if (tokens[pointer].getType == TOKEN_INTEGER) {
                // add to int_symbols
            } else if (tokens[pointer].getType == TOKEN_STRING) {
                // add to str_symbols
            }
        }
    }*/
}

void Parser::assignSymbol() {

}

void Parser::sayStatement() {

}
