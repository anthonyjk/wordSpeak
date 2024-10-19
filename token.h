#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenType {
	TOKEN_ID,
	TOKEN_STRING,
	TOKEN_INTEGER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_AS,
	TOKEN_SAY,
	TOKEN_WHILE,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_SAME,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_MORE,
	TOKEN_LESS,
	TOKEN_NOT,
	TOKEN_OPEN,
	TOKEN_CLOSE,
	TOKEN_NEWLINE,
	TOKEN_EOF
};

class Token {
public:
	Token(TokenType type, const std::string& value);
	TokenType getType() const;
	std::string getValue() const;
	void displaySelf() const;

private:
	TokenType type;
	std::string value;
};

#endif
