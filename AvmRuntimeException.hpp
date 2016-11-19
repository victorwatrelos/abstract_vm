#ifndef AVMRUNTIMEEXCEPTION_HPP
# define AVMRUNTIMEEXCEPTION_HPP

# include "LineException.hpp"
# include <stdexcept>
# include <string>

class AvmRuntimeException : public std::runtime_error, public LineException
{
	public:
		AvmRuntimeException(std::string const &str, int lineNb);
		virtual const char	*what(void) const throw();
};
#endif
