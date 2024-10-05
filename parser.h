#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <unordered_map>
#include <string>
#include <vector>

class Parser {
private:
    std::vector<Token> tokens;
    std::unordered_map<std::string, int> int_symbols;
    std::unordered_map<std::string, std::string> str_symbols;
    int pointer;

public:
    Parser(const std::vector<Token>& tokens);

    void advance();

    void parse();

    void checkID();

    void assignSymbol();

    void sayStatement();

};

#endif