#include "STDInReader.hpp"

STDInReader::STDInReader(void) {
}

STDInReader::STDInReader(const STDInReader &obj) {
	*this = obj;
}

STDInReader::~STDInReader(void) {

}

bool		STDInReader::_testLine(std::string const &line)
{
	std::string			tmpLine = "n";
	std::stringstream	tmpSs;
	Parser				parser;
	Lexer				*lexer;

	tmpSs << line << std::endl;
	lexer = new Lexer(&tmpSs);
	lexer->lex();
	parser.setTokenLst(lexer->getTokenLst());
	parser.parse();
	if (parser.hasError() || lexer->hasError())
	{
		std::cerr << "\033[1;31mThere is error on this line, would you like to retype it? [Y/n]:\033[0m";
		std::getline(std::cin, tmpLine);
	}
	if (tmpLine != "Y" && tmpLine != "y")
	{
		this->_ss << line << std::endl;
		return true;
	}
	return false;
}

void		STDInReader::read(void)
{
	std::string		line;
	size_t			length;

	std::cout << "Reading entry from stdin" << std::endl;
	while (std::getline(std::cin, line))
	{
		if ((length = line.find(";;")) != std::string::npos)
		{
			if (!this->_testLine(line.substr(0, length)))
			{
				continue ;
			}
			break;
		}
		this->_testLine(line);
	}
}

std::istream	*STDInReader::getIStream(void)
{
	return &this->_ss;
}

STDInReader	&STDInReader::operator=(const STDInReader &p) {
	(void)p;
	return *this;
}
