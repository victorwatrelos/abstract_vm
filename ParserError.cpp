#include "ParserError.hpp"

ParserError::ParserError(std::string const &str, int lineNb)
	: std::logic_error(str), LineException(lineNb)
{

}

const char	*ParserError::what(void) const throw()
{
	return ("\033[1;35mParser error (line: "
			+ std::to_string(LineException::getLine()) + ") - "  + std::logic_error::what()
			+ "\033[0m").c_str();
}
