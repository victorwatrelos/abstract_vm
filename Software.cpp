#include "Software.hpp"

Software::Software(void) {

}

Software::Software(const Software &obj) {
	*this = obj;
}

Software::~Software(void) {

}

void		Software::addIns(Instruction ins)
{
	this->_program.push_back(ins);
}

Software	&Software::operator=(const Software &p) {
	(void)p;
	return *this;
}

void		Software::disp(void)
{
	for (auto ins : this->_program)
	{
		ins.disp();
	}
}
