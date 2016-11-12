#include "Token.hpp"

Token::Token(void) {
	this->_type = Type::INSTRUCTION;
}

Token::Token(const Token &obj) {
	*this = obj;
}

Token::~Token(void) {

}

Token    &Token::operator=(const Token &p) {
	(void)p;
	return *this;
}

