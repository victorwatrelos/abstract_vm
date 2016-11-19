#include "Software.hpp"
Software::lstInsExec_t		Software::_getLstInsExec(void)
{
	lstInsExec_t		map;
	map[Instruction::InsName::ADD] = &Software::_add;
	map[Instruction::InsName::PUSH] = &Software::_push;
	map[Instruction::InsName::DUMP] = &Software::_dump;
	return map;
}

const Software::lstInsExec_t	Software::_lstInsExec = Software::_getLstInsExec();


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

void		Software::exec(void)
{
	try {
		for (auto ins : this->_program)
		{
			void (Software::* const f)(Instruction const &) = Software::_lstInsExec.at(ins.getIns());
			((*this.*f))(ins);
		}
	} catch (AvmRuntimeException &e) {
		std::cerr << e.what() << std::endl;
	}
}

void		Software::disp(void)
{
	for (auto ins : this->_program)
	{
		ins.disp();
	}
}

void	Software::_add(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

	std::cout << "Add exec" << std::endl;
	if (this->_stack.size() < 2)
	{
		throw AvmRuntimeException("Add: not enough item on stack", ins.getLine());
	}
	rhs = this->_stack.back();
	this->_stack.pop_back();
	lhs = this->_stack.back();
	this->_stack.pop_back();
	this->_stack.push_back(*lhs + *rhs);
}

void	Software::_push(Instruction const &ins)
{
	std::cout << "Push exec" << std::endl;
	this->_stack.push_back(ins.getIOperand());
}

void	Software::_dump(Instruction const &ins)
{
	std::cout << "Dump exec" << std::endl;
	for (auto iop : this->_stack)
	{
		//std::cout.precision(iop->getPrecision());
		std::cout << iop->toString() << std::endl;
	}
}
