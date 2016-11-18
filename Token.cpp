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

std::string	Token::getDataStr(const Data &data)
{
	switch (data) {
		case Data::OPEN_BRACKET:
			return "Open Bracket";
		case Data::CLOSE_BRACKET:
			return "Close Bracket";
		case Data::INS_ADD:
			return "Instruction Add";
		case Data::KEYWORD_INT32:
			return "Keyword int32";
		case Data::KEYWORD_INT16:
			return "Keyword int16";
		case Data::KEYWORD_INT8:
			return "Keyword int8";
		case Data::NONE:
			return "NONE";
	};
	return "Data Unknown";
}

std::string	Token::getTypeStr(const Type &type)
{
	switch (type) {
		case Type::INSTRUCTION:
			return "Instruction";
		case Type::BRACKET:
			return "Bracket";
		case Type::KEYWORD:
			return "Keyword";
		case Type::NUMBER:
			return "Number";
		case Type::EOL:
			return "End Of Line";
	};
	return "Type Unknown";
}

void	Token::disp(void)
{
	std::cout << "Type: " << this->getTypeStr(this->_type)
		<< " Data: " << this->getDataStr(this->_data) << std::endl;
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

