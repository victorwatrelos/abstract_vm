#ifndef STDINREADER_HPP
# define STDINREADER_HPP

# include <string>
# include <istream>
# include <sstream>
# include <iostream>
# include "Lexer.hpp"
# include "Parser.hpp"

class STDInReader
{
	public:
		STDInReader(void);
		STDInReader(const STDInReader &obj);
		STDInReader &operator=(const STDInReader &p);
		virtual ~STDInReader(void);
		void				read(void);
		std::istream		*getIStream(void);
	private:
		std::stringstream	_ss;
		bool				_testLine(std::string const &line);

};
#endif
