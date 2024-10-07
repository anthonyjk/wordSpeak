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
                pointer -= 1;
                defaultDisplay();
            }
        } else if (tokens[pointer].getType() == TOKEN_SAY) {
            sayStatement();
        } else if (tokens[pointer].getType() == TOKEN_INTEGER) {
            defaultDisplay();
        }
        advance();
    }
}

void Parser::checkID() {
    std::cout << "ID Checked!" << std::endl;
}

int Parser::expression() {

    int total = getNextInt();
    int current = 0;

    advance();

    while (tokens[pointer].getType() == TOKEN_PLUS || tokens[pointer].getType() == TOKEN_MINUS) {
        if (tokens[pointer].getType() == TOKEN_PLUS) {
            advance();
            current = getNextInt();
            total = total + current;

        } else if (tokens[pointer].getType() == TOKEN_MINUS) {
            advance();
            current = getNextInt();
            total = total - current;

        }
        advance();
    }
    return total;
}

int Parser::getNextInt() {
    int find = 0;
    if (tokens[pointer].getType() == TOKEN_ID && isIntSymbol(tokens[pointer].getValue())) {
        find = int_symbols[tokens[pointer].getValue()];
    }  else if (tokens[pointer].getType() == TOKEN_INTEGER) {
        find = std::stoi(tokens[pointer].getValue());
    } else {
        // raise error
    }

    return find;
}

void Parser::assignSymbol(Token token) {
    advance();
    if(tokens[pointer].getType() == TOKEN_INTEGER) {
        int value = expression();
        int_symbols[token.getValue()] = value;
    } else if (tokens[pointer].getType() == TOKEN_STRING) {
        str_symbols[token.getValue()] = tokens[pointer].getValue();
    } else if (tokens[pointer].getType() == TOKEN_ID) {
        if(isIntSymbol(tokens[pointer].getValue())) {
            int value = expression();
            int_symbols[token.getValue()] = value;
        }
    }
    else {
        std::cout << "Issue with assigning symbol." << std::endl;
    }
}

void Parser::defaultDisplay() {
    if (tokens[pointer].getType() == TOKEN_INTEGER) {
        int value = expression();
        std::cout << value << std::endl;
    } else if (tokens[pointer].getType() == TOKEN_ID) {
        pointer -= 1;
        sayStatement();
    }
}

void Parser::sayStatement() {
    advance(); // skip say token

    while (tokens[pointer].getType() != TOKEN_NEWLINE && tokens[pointer].getType() != TOKEN_EOF) {
        if (tokens[pointer].getType() == TOKEN_STRING) {
            std::cout << tokens[pointer].getValue();
        } else if (tokens[pointer].getType() == TOKEN_ID) {
            if (isIntSymbol(tokens[pointer].getValue())) {
                int value = expression();
                std::cout << value;
            } else if (isStrSymbol(tokens[pointer].getValue())) {
                std::cout << str_symbols[tokens[pointer].getValue()];
            }
        } else if (tokens[pointer].getType() == TOKEN_INTEGER) {
            int value = expression();
            std::cout << value;
        }

        advance();

    }
    std::cout << "\n";
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


