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
