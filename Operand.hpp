#ifndef OPERANDINTEGER_HPP
# define OPERANDINTEGER_HPP

# include "OperandFactory.hpp"
# include "IOperand.hpp"

template <typename T>
T	strTo(std::string const &str)
{
	return static_cast<T>(std::stoi(str));
}



template <typename T>
class Operand: public IOperand
{
	public:
		Operand(void);
		Operand(const Operand &obj);
		Operand&operator=(const Operand &p);
		virtual ~Operand(void)
		{
		}
		Operand(int precision, T value, const OperandFactory *factory, eOperandType type)
			: _precision(precision), _value(value), _type(type), _factory(factory), _strVal(std::to_string(value))
		{
		}
		T		getValue(void) const
		{
			return this->_value;
		}
		IOperand const * operator+(IOperand const &rhs) const
		{
			std::string tmp = std::to_string((strTo<T>(rhs.toString()) + this->_value));
			return this->_factory->createOperand(this->_type, tmp);
		}
		IOperand const * operator-(IOperand const &rhs) const
		{
			return this->_factory->createOperand(this->_type, std::to_string((strTo<T>(rhs.toString()) - this->_value)));
		}
		IOperand const * operator*(IOperand const &rhs) const
		{
			return this->_factory->createOperand(this->_type, std::to_string((strTo<T>(rhs.toString()) * this->_value)));
		}
		IOperand const * operator/(IOperand const &rhs) const
		{
			return this->_factory->createOperand(this->_type, std::to_string((strTo<T>(rhs.toString()) / this->_value)));
		}
		IOperand const * operator%(IOperand const &rhs) const
		{
			return this->_factory->createOperand(this->_type, std::to_string((strTo<T>(rhs.toString()) % this->_value)));
		}
		std::string const	&toString(void) const
		{
			return this->_strVal;
		}
		eOperandType	getType(void) const
		{
			return this->_type;
		}
		int		getPrecision( void ) const
		{
			return this->_precision;
		}
	private:
		int		_precision;
		T		_value;
		eOperandType	_type;
		const OperandFactory	*_factory;
		std::string		_strVal;
};

template <typename T>
std::string	floating_modulo(T lhs, std::string rhs)
{
	return std::to_string(lhs - static_cast<T>(static_cast<int>(lhs / std::stod(rhs))));
}

template <>
inline IOperand const *Operand<float>::operator%(IOperand const &rhs) const
{
	return this->_factory->createOperand(this->_type, (floating_modulo<float>(this->_value, rhs.toString())));
}
template <>
inline IOperand const *Operand<double>::operator%(IOperand const &rhs) const
{
	return this->_factory->createOperand(this->_type, (floating_modulo<double>(this->_value, rhs.toString())));
}
#endif
