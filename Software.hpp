#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include "Instruction.hpp"
# include "OperandFactory.hpp"
# include "AvmRuntimeException.hpp"
# include <limits>
# include <vector>

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
		OperandFactory					_factory;
		bool							_isFinished = false;

		void							_add(Instruction const &ins);
		void							_push(Instruction const &ins);
		void							_dump(Instruction const &ins);
		void							_pop(Instruction const &ins);
		void							_assert(Instruction const &ins);
		void							_sub(Instruction const &ins);
		void							_mul(Instruction const &ins);
		void							_div(Instruction const &ins);
		void							_mod(Instruction const &ins);
		void							_print(Instruction const &ins);
		void							_exit(Instruction const &ins);

		static const lstInsExec_t		_lstInsExec;	
		static lstInsExec_t				_getLstInsExec(void);
};
#endif
