#ifndef AVMOVERFLOWERROR_HPP
# define AVMOVERFLOWERROR_HPP

# include <stdexcept>
# include <string>

class AvmOverflowError : public std::overflow_error
{
	public:
		AvmOverflowError(std::string const &str);
};
#endif
