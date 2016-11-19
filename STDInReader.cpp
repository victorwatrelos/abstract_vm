#include "STDInReader.hpp"

STDInReader::STDInReader(void) {
}

STDInReader::STDInReader(const STDInReader &obj) {
	*this = obj;
}

STDInReader::~STDInReader(void) {

}

void		STDInReader::read(void)
{
	std::string		line;
	size_t			length;

	std::cout << "Reading entry from stdin" << std::endl;
	std::cout << ">";
	while (std::getline(std::cin, line))
	{
		if ((length = line.find(";;")) != std::string::npos)
		{
			this->_ss << line.substr(0, length) << std::endl;
			break;
		}
		this->_ss << line << std::endl;
		std::cout << ">";
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
