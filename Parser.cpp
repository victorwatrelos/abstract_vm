#include "Parser.hpp"

Parser::Parser(void) {

}

Parser::Parser(const Parser &obj) {
	*this = obj;
}

Parser::~Parser(void) {

}

void		Parser::setTokenLst(const std::vector<Token> &lstToken)
{
	this->_tokenLst = lstToken;
}

Parser    &Parser::operator=(const Parser &p) {
	(void)p;
	return *this;
}

