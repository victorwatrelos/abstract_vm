#include "LineException.hpp"

LineException::LineException(void) 
	: _line(-1)
{
}

LineException::LineException(int line) 
	: _line(line)
{
}

LineException::LineException(const LineException &obj) {
	*this = obj;
}

LineException::~LineException(void)
{

}

int				LineException::getLine(void) const
{
	return this->_line;
}

LineException	&LineException::operator=(const LineException &p) {
	this->_line = p.getLine();
	return *this;
}
