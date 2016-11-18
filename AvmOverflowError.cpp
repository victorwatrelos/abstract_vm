#include "AvmOverflowError.hpp"

AvmOverflowError::AvmOverflowError(std::string const &str)
	: std::overflow_error("Overflow: " + str)
{
}
