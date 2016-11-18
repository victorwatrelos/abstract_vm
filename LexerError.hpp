#ifndef LEXERERROR_HPP
# define LEXERERROR_HPP

# include <stdexcept>
# include <string>
# include "LineException.hpp"

class LexerError : public std::logic_error, LineException
{
	public:
		LexerError(std::string const &str, int lineNb);
		virtual const char	*what(void) const throw();
};
#endif
