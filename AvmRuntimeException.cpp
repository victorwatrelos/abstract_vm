#include "AvmRuntimeException.hpp"

AvmRuntimeException::AvmRuntimeException(std::string const &str)
	: std::runtime_error(str)
{
}
