#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <map>
# include <limits>
# include "IOperand.hpp"
# include "AvmOverflowError.hpp"

class OperandFactory
{
	public:
		typedef	std::map<eOperandType, IOperand const* (OperandFactory::*)(std::string const &) const> lstOp_t;
		OperandFactory(void);
		OperandFactory(const OperandFactory &obj);
		OperandFactory &operator=(const OperandFactory &p);
		virtual ~OperandFactory(void);
		IOperand const *createOperand(eOperandType type, std::string const & value) const;
	private:
		static const lstOp_t	_lstOp;	

		IOperand const *_createInt8Op(const std::string &val) const;
		IOperand const *_createInt16Op(const std::string &val) const;
		IOperand const *_createInt32Op(const std::string &val) const;
		IOperand const *_createFloatOp(const std::string &val) const;
		IOperand const *_createDoubleOp(const std::string &val) const;
		static lstOp_t	getLstOp(void);
};
#endif
