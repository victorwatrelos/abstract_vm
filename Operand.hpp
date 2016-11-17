#ifndef OPERANDINTEGER_HPP
# define OPERANDINTEGER_HPP

# include "OperandFactory.hpp"
# include "IOperand.hpp"
# include <sstream>
# include <iomanip>

template <typename T>
T	strTo(std::string const &str)
{
	return static_cast<T>(std::stoi(str));
}
# include <iostream>

template <>
float	strTo(std::string const &str)
{
	std::cout << "FLOAT" << str << std::endl;
	return std::stof(str);
}

template <>
double	strTo(std::string const &str)
{
	std::cout << "Double" << str << std::endl;
	return std::stod(str);
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
			: _precision(precision), _value(value), _type(type), _factory(factory), _strVal(this->_toString(value))
		{
			std::cout << "there val: " << static_cast<int>(value) << "|" << std::endl;
		}
		T		getValue(void) const
		{
			return this->_value;
		}
		IOperand const *operator+(IOperand const &rhs) const
		{
			if (rhs.getType() > this->_type)
			{
				return rhs + *this;
			}
			std::string tmp = this->_toString((strTo<T>(rhs.toString()) + this->_value));
			return this->_factory->createOperand(this->_type, tmp);
		}
		IOperand const *operator-(IOperand const &rhs) const
		{
			if (rhs.getType() > this->_type)
			{
				return rhs - *this;
			}
			return this->_factory->createOperand(this->_type, this->_toString((strTo<T>(rhs.toString()) - this->_value)));
		}
		IOperand const *operator*(IOperand const &rhs) const
		{
			if (rhs.getType() > this->_type)
			{
				return rhs * *this;
			}
			return this->_factory->createOperand(this->_type, this->_toString((strTo<T>(rhs.toString()) * this->_value)));
		}
		IOperand const *operator/(IOperand const &rhs) const
		{
			if (rhs.getType() > this->_type)
			{
				return rhs / *this;
			}
			return this->_factory->createOperand(this->_type, this->_toString((strTo<T>(rhs.toString()) / this->_value)));
		}
		IOperand const *operator%(IOperand const &rhs) const
		{
			if (rhs.getType() > this->_type)
			{
				return rhs % *this;
			}
			return this->_factory->createOperand(this->_type, this->_toString((strTo<T>(rhs.toString()) % this->_value)));
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
		std::string		_toString(T val) const
		{
			std::stringstream ss;

			ss << std::fixed << std::setprecision(this->_precision) << val;
			return ss.str();
		}
};

template <typename T>
T	floating_modulo(T lhs, std::string rhs)
{
	return lhs - static_cast<T>(static_cast<int>(lhs / std::stod(rhs)));
}

template <>
inline IOperand const *Operand<float>::operator%(IOperand const &rhs) const
{
	return this->_factory->createOperand(this->_type,
			this->_toString((floating_modulo<float>(this->_value, rhs.toString()))));
}
template <>
inline IOperand const *Operand<double>::operator%(IOperand const &rhs) const
{
	return this->_factory->createOperand(this->_type,
			this->_toString((floating_modulo<double>(this->_value, rhs.toString()))));
}
#endif
