#include "Software.hpp"
Software::lstInsExec_t		Software::_getLstInsExec(void)
{
	lstInsExec_t		map;
	map[Instruction::InsName::ADD] = &Software::_add;
	map[Instruction::InsName::PUSH] = &Software::_push;
	map[Instruction::InsName::DUMP] = &Software::_dump;
	map[Instruction::InsName::POP] = &Software::_pop;
	map[Instruction::InsName::ASSERT] = &Software::_assert;
	map[Instruction::InsName::SUB] = &Software::_sub;
	map[Instruction::InsName::MUL] = &Software::_mul;
	map[Instruction::InsName::DIV] = &Software::_div;
	map[Instruction::InsName::MOD] = &Software::_mod;
	map[Instruction::InsName::PRINT] = &Software::_print;
	map[Instruction::InsName::EXIT] = &Software::_exit;
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
			if (this->_isFinished)
				break ;
		}
		if (!this->_isFinished )
			std::cerr << "\033[1;31mRuntime exception - Program not finished with exit instruction\033[0m" << std::endl;
	} catch (AvmRuntimeException &e) {
		std::cerr << e.what() << std::endl;
	} catch (AvmOverflowError &e) {
		std::cerr << e.what() << std::endl;
	}
}

void	Software::_add(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

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
	this->_stack.push_back(ins.getIOperand());
}

void	Software::_dump(Instruction const &ins)
{
	(void)ins;
	for (auto iop : this->_stack)
	{
		std::cout << iop->toString() << std::endl;
	}
}

void	Software::_pop(Instruction const &ins)
{
	if (this->_stack.size() < 1)
		throw AvmRuntimeException("Pop: empty stack", ins.getLine());
	this->_stack.pop_back();
}

void	Software::_assert(Instruction const &ins)
{
	IOperand const	*insIOP, *stackIOP;

	if (this->_stack.size() < 1)
	{
		throw AvmRuntimeException("Assert: empty stack", ins.getLine());
	}
	insIOP = ins.getIOperand();
	stackIOP = this->_stack.back();
	if (insIOP->getType() > stackIOP->getType())
	{
		stackIOP = this->_factory.createOperand(insIOP->getType(), stackIOP->toString());
	} else if (insIOP->getType() < stackIOP->getType()) {
		insIOP = this->_factory.createOperand(stackIOP->getType(), insIOP->toString());
	}
	if (insIOP->toString() != stackIOP->toString())
	{
		throw AvmRuntimeException("Assert: "
				+ insIOP->toString() + " != " + stackIOP->toString(), ins.getLine());
	}
}

void	Software::_sub(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

	if (this->_stack.size() < 2)
	{
		throw AvmRuntimeException("Sub: not enough item on stack", ins.getLine());
	}
	rhs = this->_stack.back();
	this->_stack.pop_back();
	lhs = this->_stack.back();
	this->_stack.pop_back();
	this->_stack.push_back(*lhs - *rhs);
}

void	Software::_mul(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

	if (this->_stack.size() < 2)
	{
		throw AvmRuntimeException("Mul: not enough item on stack", ins.getLine());
	}
	rhs = this->_stack.back();
	this->_stack.pop_back();
	lhs = this->_stack.back();
	this->_stack.pop_back();
	this->_stack.push_back(*lhs * *rhs);
}

void	Software::_div(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

	if (this->_stack.size() < 2)
	{
		throw AvmRuntimeException("Div: not enough item on stack", ins.getLine());
	}
	rhs = this->_stack.back();
	this->_stack.pop_back();
	lhs = this->_stack.back();
	this->_stack.pop_back();
	if (rhs->toString() == "0")
	{
		throw AvmRuntimeException("Div: Division by zero, END OF THE WORLD!!!!!", ins.getLine());
	}
	this->_stack.push_back(*lhs / *rhs);
}

void	Software::_mod(Instruction const &ins)
{
	IOperand const	*rhs;
	IOperand const	*lhs;

	if (this->_stack.size() < 2)
	{
		throw AvmRuntimeException("Mod: not enough item on stack", ins.getLine());
	}
	rhs = this->_stack.back();
	this->_stack.pop_back();
	lhs = this->_stack.back();
	this->_stack.pop_back();
	if (rhs->toString() == "0")
	{
		throw AvmRuntimeException("Mod: Modulo by zero, END OF THE WORLD!!!!!", ins.getLine());
	}
	this->_stack.push_back(*lhs % *rhs);
}

void	Software::_print(Instruction const &ins)
{
	if (this->_stack.back()->getType() != eOperandType::INT_8)
	{
		throw AvmRuntimeException("Print: Operand not an int8", ins.getLine());
	}
	std::cout << static_cast<int8_t>(std::stoi(this->_stack.back()->toString())) << std::endl;
}

void	Software::_exit(Instruction const &ins)
{
	(void)ins;
	this->_isFinished = true;
}

