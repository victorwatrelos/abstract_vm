#ifndef AVMRUNTIMEEXCEPTION_HPP
# define AVMRUNTIMEEXCEPTION_HPP

# include <stdexcept>

class AvmRuntimeException : public std::runtime_error
{
	public:
		AvmRuntimeException(std::string const &str);
};
#endif
