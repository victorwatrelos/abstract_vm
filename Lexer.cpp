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

void	Lexer::_endOfToken(void)
{
	if (this->_buffer.length() > 0)
	{
		this->_addToken(this->_buffer);
		std::cout << "buff: " << this->_buffer << std::endl;
		this->_buffer = "";
	}
}

void	Lexer::_processLine(const std::string &line)
{
	for (auto i : line)
	{
		if (Lexer::_isSeparator(i)) {
			this->_endOfToken();
		} else {
			this->_buffer += i;
		}
		std::cout << i;
	}
	std::cout << std::endl;
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

