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

    int expression();

    int getNextInt();

    void assignSymbol(Token token);

    void defaultDisplay();

    void sayStatement();

    bool isIntSymbol(std::string symbol) const;

    bool isStrSymbol(std::string symbol) const;

    void conditional();

    void whileLoop();
};

#endif
