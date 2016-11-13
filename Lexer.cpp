#include "Lexer.hpp"

Lexer::Lexer(std::istream *ist)
	: _ist(ist)
{
}

Lexer::Lexer(const Lexer &obj) {
	*this = obj;
}

Lexer::~Lexer(void) {

}

std::istream	*Lexer::getIst() const
{
	return this->_ist;
}

void	Lexer::lex()
{
	this->_browseLine();
}

bool	Lexer::_isSeparator(const char &c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return true;
	return false;
}

void	Lexer::_addToken(std::string elem)
{
	std::cout << "Elem: " << elem << std::endl;
}

Token	Lexer::_getToken(const Token::Type &type, const Data &data) const
{
	return Token(type, data, this->_filename, this->_currentLine);
}

void	Lexer::_endOfToken(void)
{
	if (this->_buffer.length() > 0)
	{
		this->_addToken(this->_buffer);
		this->_buffer = "";
	}
}

bool	Lexer::_isBracket(const char &c)
{
	if (c == '(' || c == ')')
		return true;
	return false;
}

void	Lexer::_addBracketToken(const char &c)
{
	if (c == '(') {
		this->_lstToken.push_back(
				this->_getToken(Token::Type::BRACKET, Token::Data::OPEN_BRACKET)
				);
	} else if (c == ')') {
		this->_lstToken.push_back(
				this->_getToken(Token::Type::BRACKET, Token::Data::CLOSE_BRACKET)
				);
	}
}

void	Lexer::_processLine(const std::string &line)
{
	for (auto i : line)
	{
		if (Lexer::_isSeparator(i)) {
			this->_endOfToken();
		} else if (Lexer::_isBracket(i)) {
			this->_addBracketToken(i);
			this->_endOfToken();
		} else {
			this->_buffer += i;
		}
	}
	this->_endOfToken();
}

void	Lexer::_browseLine() {
	std::string		line;

	this->_currentLine = 1;
	while (std::getline(*this->_ist, line))
	{
		std::cout << "Line: " << line << std::endl;
		this->_processLine(line);
		this->_currentLine++;
	}
}

Lexer    &Lexer::operator=(const Lexer &p) {
	this->_ist = p.getIst();
	return *this;
}

