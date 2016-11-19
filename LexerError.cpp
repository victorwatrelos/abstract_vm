#include "LexerError.hpp"

LexerError::LexerError(std::string const &str, int lineNb)
	: std::logic_error(str), LineException(lineNb)
{

}

const char	*LexerError::what(void) const throw()
{
	return ("\033[1;33mLexer error (line: "
			+ std::to_string(LineException::getLine()) + ") - "  + std::logic_error::what() + "\033[0m").c_str();
}
