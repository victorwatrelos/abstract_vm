#include "Token.hpp"

Token::Token(void) 
	: _type(Type::INSTRUCTION), _data(Data::NONE)
{
}

Token::Token(const Token &obj) {
	*this = obj;
}

Token::Token(const Type &token_type, const Data &data, const std::string &filename, int line) 
	: _type(token_type), _data(data), _filename(filename), _line(line)
{
}

Token::Token(const std::string &number, const std::string &filename, int line)
	: _type(Type::NUMBER), _data(Data::NONE), _filename(filename), _line(line), _number(number)
{
}

Token::~Token(void) {

}

std::string const	&Token::getNumber(void) const
{
	if (this->_type != Type::NUMBER)
		throw new std::exception;
	return this->_number;
}

Token::Type	Token::getType(void) const
{
	return this->_type;
}

Token::Data	Token::getData(void) const
{
	return this->_data;
}

std::string	Token::getFilename(void) const
{
	return this->_filename;
}

int		Token::getLine(void) const
{
	return this->_line;
}

Token    &Token::operator=(const Token &p) {
	this->_line = p.getLine();
	this->_type = p.getType();
	this->_data = p.getData();
	this->_filename = p.getFilename();
	if (p.getType() == Type::NUMBER)
		this->_number = p.getNumber();
	return *this;
}

