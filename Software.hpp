#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include <vector>
# include "Instruction.hpp"
# include "AvmRuntimeException.hpp"
# include <limits>

typedef std::numeric_limits< double > dbl;

class Software
{
	public:
		typedef	std::map<Instruction::InsName, void (Software::*)(Instruction const &)> lstInsExec_t;
		Software(void);
		Software(const Software &obj);
		Software &operator=(const Software &p);
		void	addIns(Instruction ins);
		virtual ~Software(void);
		void	disp(void);
		void	exec(void);
	private:
		std::vector<Instruction>		_program;
		std::vector<IOperand const *>	_stack;
		static const lstInsExec_t		_lstInsExec;	
		static lstInsExec_t				_getLstInsExec(void);
		void							_add(Instruction const &ins);
		void							_push(Instruction const &ins);
		void							_dump(Instruction const &ins);
};
#endif
