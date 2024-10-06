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
        if(tokens[pointer].getType() == TOKEN_ID) {
            Token id_token = tokens[pointer];
            advance();
            if (tokens[pointer].getType() == TOKEN_AS) {
                assignSymbol(id_token);
            } else {
                // print out symbol, if other things in line before NL then return error?
            }
        } else if (tokens[pointer].getType() == TOKEN_SAY) {
            sayStatement();
        }
        advance();
    }
}

void Parser::checkID() {
    std::cout << "ID Checked!" << std::endl;
}

void Parser::assignSymbol(Token token) {
    advance();
    if(tokens[pointer].getType() == TOKEN_INTEGER) {
        int_symbols[token.getValue()] = std::stoi(tokens[pointer].getValue());
    } else if (tokens[pointer].getType() == TOKEN_STRING) {
        str_symbols[token.getValue()] = tokens[pointer].getValue();
    } else {
        std::cout << "Issue with assigning symbol." << std::endl;
    }
}

void Parser::sayStatement() {
    advance(); // skip say token
    while (tokens[pointer].getType() != TOKEN_NEWLINE && tokens[pointer].getType() != TOKEN_EOF) {
        if (tokens[pointer].getType() == TOKEN_STRING) {
            std::cout << tokens[pointer].getValue();
        } else if (tokens[pointer].getType() == TOKEN_ID) {
            if (isIntSymbol(tokens[pointer].getValue())) {
                std::cout << int_symbols[tokens[pointer].getValue()];
            } else if (isStrSymbol(tokens[pointer].getValue())) {
                std::cout << str_symbols[tokens[pointer].getValue()];
            }
        }

        advance();

    }
}

bool Parser::isIntSymbol(std::string symbol) const {
    if(int_symbols.count(symbol) > 0) {
        return true;
    }
    return false;
}

bool Parser::isStrSymbol(std::string symbol) const {
    if(str_symbols.count(symbol) > 0) {
        return true;
    }
    return false;
}


