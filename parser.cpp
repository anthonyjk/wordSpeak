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
        switch(tokens[pointer].getType()) {
            case TOKEN_ID:
                {
                    Token id_token = tokens[pointer];
                    advance();
                    if (tokens[pointer].getType() == TOKEN_AS) {
                        assignSymbol(id_token);
                    } else {
                        pointer -= 1;
                        defaultDisplay();
                    }
                }
                break;
            case TOKEN_SAY:
                sayStatement();
                break;
            case TOKEN_INTEGER:
                defaultDisplay();
                break;
            case TOKEN_IF:
                {
                    std::vector<Token> conditions = collectConditional();
                    if(!conditionTrue(conditions)){
                        skipCondition();
                    }
                }
                break;
            case TOKEN_WHILE:
                whileLoop();
                break;
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
        pointer--;
        sayStatement();
    }
}

void Parser::sayStatement() {
    advance(); // skip say token

    while (tokens[pointer].getType() != TOKEN_NEWLINE && tokens[pointer].getType() != TOKEN_EOF) {
        switch(tokens[pointer].getType()) {
            case TOKEN_STRING:
                std::cout << tokens[pointer].getValue();
                break;
            case TOKEN_INTEGER:
                {
                    int value = expression();
                    std::cout << value;
                }
                break;
            case TOKEN_ID:
                {
                    if (isIntSymbol(tokens[pointer].getValue())) {
                        int value = expression();
                        std::cout << value;
                    } else if (isStrSymbol(tokens[pointer].getValue())) {
                        std::cout << str_symbols[tokens[pointer].getValue()];
                    }
                }
                break;
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

std::vector<Token> Parser::collectConditional() {
    std::vector<Token> conditions;
    advance();
    while(tokens[pointer].getType() != TOKEN_OPEN) {
        if(tokens[pointer].getType() == TOKEN_NEWLINE || tokens[pointer].getType() == TOKEN_EOF) {
            std::cout << "Invalid Syntax" << std::endl;
            break;
        }

        if(tokens[pointer].getType() == TOKEN_INTEGER || (tokens[pointer].getType() == TOKEN_ID && isIntSymbol(tokens[pointer].getValue()))) {
            int value = expression();
            conditions.push_back(Token(TokenType::TOKEN_INTEGER, std::to_string(value)));
            pointer--; // Handles over stepping
        } else {
            conditions.push_back(tokens[pointer]);
        }
        advance();
    }

    return conditions;
}

bool Parser::conditionTrue(std::vector<Token> conditions) {

    int c_left = std::stoi(conditions[0].getValue());
    int c_right = std::stoi(conditions[2].getValue());
    if(conditions.size() == 3) {
        switch(conditions[1].getType()) {
            case TOKEN_LESS:
                return(c_left < c_right);
                break;
            case TOKEN_MORE:
                return(c_left > c_right);
                break;
            case TOKEN_SAME:
                return(c_left == c_right);
                break;
            case TOKEN_NOT:
                return(c_left != c_right);
                break;
        }
    }
    return false;

    // Handle 'and' and 'or' statements later (outside of this func, should be calling this func twice)
}

void Parser::whileLoop() {
    int init_pointer = pointer;
    std::vector<Token> conditions = collectConditional();

    if(conditionTrue(conditions)) {
        whileParse(init_pointer);
    } else {
        skipCondition();
    }

}

void Parser::whileParse(int init_pointer) {
    int prev_close = 0;
    bool isMet = true;
    while(pointer < tokens.size() && isMet) {
        switch(tokens[pointer].getType()) {
            case TOKEN_ID:
            {
                Token id_token = tokens[pointer];
                advance();
                if (tokens[pointer].getType() == TOKEN_AS) {
                    assignSymbol(id_token);
                } else {
                    pointer -= 1;
                    defaultDisplay();
                }
            }
            break;
            case TOKEN_SAY:
                sayStatement();
                pointer -= 2;
                break;
            case TOKEN_INTEGER:
                defaultDisplay();
                break;
            case TOKEN_IF:
            {
                std::vector<Token> conditions = collectConditional();
                if(!conditionTrue(conditions)){
                    skipCondition();
                } else {
                    prev_close++;
                }
            }
            break;
            case TOKEN_WHILE:
                whileLoop();
                break;
            case TOKEN_CLOSE:
                if(prev_close > 0) {
                    prev_close--;
                } else {
                    isMet = false;
                }
                break;
        }
        advance();
    }

    pointer = init_pointer;
    whileLoop();
}

void Parser::skipCondition() {
    while(tokens[pointer].getType() != TOKEN_CLOSE) {
        pointer++;
    }
}

