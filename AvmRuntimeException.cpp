#include "AvmRuntimeException.hpp"

AvmRuntimeException::AvmRuntimeException(std::string const &str, int lineNb)
	: std::runtime_error(str), LineException(lineNb)
{
}

const char	*AvmRuntimeException::what(void) const throw()
{
	return ("Runtime exception (line: " + std::to_string(LineException::getLine()) + ") - " + std::runtime_error::what()).c_str();
}
