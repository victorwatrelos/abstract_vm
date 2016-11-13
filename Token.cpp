#include "Token.hpp"

Token::Token(void) {
	this->_type = Type::INSTRUCTION;
}

Token::Token(const Token &obj) {
	*this = obj;
}

Token::Token(const Type &token_type, const Data &data, const std::string &filename, int line) 
	: _type(token_type), _data(data), _filename(filename), _line(line)
{
}
Token::~Token(void) {

}

Token    &Token::operator=(const Token &p) {
	(void)p;
	return *this;
}

