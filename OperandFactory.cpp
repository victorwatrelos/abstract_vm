#include "OperandFactory.hpp"
#include "Operand.hpp"
OperandFactory::lstOp_t		OperandFactory::getLstOp(void)
{
	lstOp_t		map;

	map[eOperandType::INT_8] = &OperandFactory::_createInt8Op;
	map[eOperandType::INT_16] = &OperandFactory::_createInt16Op;
	map[eOperandType::INT_32] = &OperandFactory::_createInt32Op;
	map[eOperandType::FLOAT] = &OperandFactory::_createFloatOp;
	map[eOperandType::DOUBLE] = &OperandFactory::_createDoubleOp;
	return map;
}


const	OperandFactory::lstOp_t		OperandFactory::_lstOp = OperandFactory::getLstOp();

OperandFactory::OperandFactory(void) {
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
	std::cout << "VAL IN: " << val << "|" << std::endl;
	std::cout << "Val after: " << std::stoi(val) << std::endl;
	return new Operand<int8_t>(3, std::stoi(val), this, eOperandType::INT_8);
}

IOperand const *	OperandFactory::_createInt16Op(const std::string &val) const
{
	std::cout << "VAL IN: " << val << "|" << std::endl;
	return new Operand<int16_t>(5, std::stoi(val), this, eOperandType::INT_16);
}

IOperand const *	OperandFactory::_createInt32Op(const std::string &val) const
{
	std::cout << "VAL IN: " << val << "|" << std::endl;
	return new Operand<int32_t>(10, std::stoi(val), this, eOperandType::INT_32);
}

IOperand const *	OperandFactory::_createFloatOp(const std::string &val) const
{
	int	precision = std::numeric_limits< float >::max_digits10;
	std::cout << "VAL FO: " << val << "|" << std::endl;
	return new Operand<float>(precision, std::stof(val), this, eOperandType::FLOAT);
}

IOperand const *	OperandFactory::_createDoubleOp(const std::string &val) const
{
	int	precision = std::numeric_limits< double>::max_digits10;
	std::cout << "VAL DO: " << val << "|" << std::endl;
	return new Operand<double>(precision, std::stod(val), this, eOperandType::DOUBLE);
}

