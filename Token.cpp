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

Token::Token(const int number, const std::string &filename, int line)
	: _type(Type::NUMBER_INT), _filename(filename), _line(line), _numberInt(number)
{
}
Token::Token(const double number, const std::string &filename, int line)
	: _type(Type::NUMBER_FLOAT), _filename(filename), _line(line), _numberFloat(number)
{
}

Token::~Token(void) {

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
		case Type::NUMBER_INT:
			return "Number integer";
		case Type::NUMBER_FLOAT:
			return "Number float";
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
	return *this;
}

