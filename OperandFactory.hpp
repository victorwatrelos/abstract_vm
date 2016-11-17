#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <map>
# include "IOperand.hpp"

class OperandFactory
{
	public:
		OperandFactory(void);
		OperandFactory(const OperandFactory &obj);
		OperandFactory &operator=(const OperandFactory &p);
		virtual ~OperandFactory(void);
		IOperand const *createOperand( eOperandType type, std::string const & value ) const;
	private:
		std::map<eOperandType, IOperand const* (OperandFactory::*)(std::string const & value) const>	_lstOp;	

		IOperand const *_createInt8Op(const std::string &val) const;
		IOperand const *_createInt16Op(const std::string &val) const;
		IOperand const *_createInt32Op(const std::string &val) const;
		IOperand const *_createFloatOp(const std::string &val) const;
		IOperand const *_createDoubleOp(const std::string &val) const;
};
#endif
