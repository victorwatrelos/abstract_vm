#include "Instruction.hpp"

Instruction::ins_to_string_t			Instruction::_create_ins_to_string(void)
{
	ins_to_string_t		map;

	map[InsName::ADD] = "ADD";
	map[InsName::PUSH] = "PUSH";
	return map;
}

const Instruction::ins_to_string_t		Instruction::_insToString = Instruction::_create_ins_to_string();


Instruction::Instruction(void)
{
}

Instruction::Instruction(IOperand const *param, InsName const &ins)
	: _ins(ins), _param(param)
{
	if (!param)
		return;
	this->_hasParam = true;
}

Instruction::InsName		Instruction::getIns(void) const
{
	return this->_ins;
}

void						Instruction::disp(void) const
{
	std::cout << this->_insToString.at(this->_ins) << std::endl;
}

IOperand const				*Instruction::getIOperand(void) const
{
	return this->_param;
}

Instruction::Instruction(const Instruction &obj) {
	*this = obj;
}

Instruction::~Instruction(void) {

}

Instruction	&Instruction::operator=(const Instruction &p) {
	this->_ins = p.getIns();
	this->_param = p.getIOperand();
	this->_hasParam = this->_param != nullptr;
	return *this;
}
