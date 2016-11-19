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

std::vector<IOperand const *>	OperandFactory::_lstIop = std::vector<IOperand const *>();

const	OperandFactory::lstOp_t		OperandFactory::_lstOp = OperandFactory::getLstOp();

OperandFactory::OperandFactory(void) {
}

OperandFactory::OperandFactory(const OperandFactory &obj) {
	*this = obj;
}

OperandFactory::~OperandFactory(void) {

}

void			OperandFactory::deleteOp(void)
{
	for (auto op : OperandFactory::_lstIop)
	{
		delete op;
	}
}

OperandFactory	&OperandFactory::operator=(const OperandFactory &p) {
	(void)p;
	return *this;
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const	*(OperandFactory::*f)(std::string const &value) const;
	f = this->_lstOp.at(type);
	IOperand const	*iop = (*this.*f)(value);
	OperandFactory::_lstIop.push_back(iop);
	return iop;
}

IOperand const *	OperandFactory::_createInt8Op(const std::string &val) const
{
	int		res;

	try {
		res = std::stoi(val);
	} catch (std::out_of_range &e) {
		throw AvmOverflowError("Int 8: " + val);
	}
	if (res > std::numeric_limits<int8_t>::max()
			|| res < std::numeric_limits<int8_t>::min())
	{
		throw AvmOverflowError("Int 8: " + val);
	}
	return new Operand<int8_t>(3, res, this, eOperandType::INT_8);
}

IOperand const *	OperandFactory::_createInt16Op(const std::string &val) const
{
	int		res;

	try {
		res = std::stoi(val);
	} catch (std::out_of_range &e) {
		throw AvmOverflowError("Int 16: " + val);
	}
	if (res > std::numeric_limits<int16_t>::max()
			|| res < std::numeric_limits<int16_t>::min())
	{
		std::cout << std::numeric_limits<int16_t>::min() << "MAX" << std::endl;
		throw AvmOverflowError("Int 16: " + val);
	}
	return new Operand<int16_t>(5, res, this, eOperandType::INT_16);
}

IOperand const *	OperandFactory::_createInt32Op(const std::string &val) const
{
	int		res;

	try {
		res = std::stoi(val);
	} catch (std::out_of_range &e) {
		throw AvmOverflowError("Int 32: " + val);
	}
	if (res > std::numeric_limits<int32_t>::max()
			|| res < std::numeric_limits<int32_t>::min())
	{
		throw AvmOverflowError("Int 32: " + val);
	}
	return new Operand<int32_t>(10, res, this, eOperandType::INT_32);
}

IOperand const *	OperandFactory::_createFloatOp(const std::string &val) const
{
	float		res;

	try {
		res = std::stof(val);
	} catch (std::out_of_range &e) {
		throw AvmOverflowError("Float: " + val);
	}

	int	precision = std::numeric_limits< float >::max_digits10;
	return new Operand<float>(precision, res, this, eOperandType::FLOAT);
}

IOperand const *	OperandFactory::_createDoubleOp(const std::string &val) const
{
	double		res;

	try {
		res = std::stod(val);
	} catch (std::out_of_range &e) {
		throw AvmOverflowError("Double: " + val);
	}

	int	precision = std::numeric_limits< double>::max_digits10;
	return new Operand<double>(precision, res, this, eOperandType::DOUBLE);
}
