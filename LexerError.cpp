#include "LexerError.hpp"

LexerError::LexerError(std::string const &str, int lineNb)
	: std::logic_error(str), LineException(lineNb)
{

}

const char	*LexerError::what(void) const throw()
{
	return ("Lexer error (line: " + std::to_string(LineException::getLine()) + ") - "  + std::logic_error::what()).c_str();
}
