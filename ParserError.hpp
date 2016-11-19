#ifndef PARSERERROR_HPP
# define PARSERERROR_HPP

# include <stdexcept>
# include <string>
# include "LineException.hpp"

class ParserError : public std::logic_error, public LineException
{
	public:
		ParserError(std::string const &str, int lineNb);
		virtual const char	*what(void) const throw();
	private:
};
#endif
