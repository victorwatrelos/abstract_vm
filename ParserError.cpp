#include "ParserError.hpp"

ParserError::ParserError(std::string const &str, int lineNb)
	: std::logic_error(str), LineException(lineNb)
{

}

const char	*ParserError::what(void) const throw()
{
	return ("Parser error (line: " + std::to_string(LineException::getLine()) + ") - "  + std::logic_error::what()).c_str();
}
