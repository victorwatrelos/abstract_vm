#include "AvmOverflowError.hpp"

AvmOverflowError::AvmOverflowError(std::string const &str)
	: std::overflow_error("\033[1;31mOverflow - " + str + "\033[0m")
{
}
