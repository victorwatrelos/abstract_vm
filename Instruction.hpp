#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include "IOperand.hpp"
# include "Token.hpp"
# include <map>


class Instruction
{
	public:
		enum class InsName {ADD, PUSH, DUMP, POP, ASSERT, SUB, MUL, DIV, MOD, PRINT, EXIT};
		typedef std::map<InsName, std::string>	ins_to_string_t;
		Instruction(void);
		Instruction(IOperand const *param, InsName const &ins, int line);
		Instruction(const Instruction &obj);
		Instruction &operator=(const Instruction &p);
		virtual ~Instruction(void);
		InsName			getIns(void) const;
		IOperand const	*getIOperand(void) const;
		void			disp(void) const;
		int				getLine(void) const;

	private:
		InsName			_ins;
		IOperand const	*_param;
		bool			_hasParam = false;
		static const ins_to_string_t	_insToString;
		static ins_to_string_t			_create_ins_to_string(void);
		int					_line;
};
#endif
