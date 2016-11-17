#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory(void) {
	this->_lstOp[eOperandType::INT_8] = &OperandFactory::_createInt8Op;
}

OperandFactory::OperandFactory(const OperandFactory &obj) {
	*this = obj;
}

OperandFactory::~OperandFactory(void) {

}

OperandFactory	&OperandFactory::operator=(const OperandFactory &p) {
	(void)p;
	return *this;
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const	*(OperandFactory::*f)(std::string const &value) const;
	f = this->_lstOp.at(type);
	return (*this.*f)(value);
}

IOperand const *	OperandFactory::_createInt8Op(const std::string &val) const
{
	return new Operand<int8_t>(8, std::stoi(val), this, eOperandType::INT_8);
}
