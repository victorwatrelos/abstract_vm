#ifndef INSTRUCTIONINFO_HPP
# define INSTRUCTIONINFO_HPP

# include "Instruction.hpp"
# include <map>

class InstructionInfo
{
	public:
		static std::map<Instruction::InsName, bool>			create_has_param();
		static bool											hasParam(Instruction::InsName);
	private:
		static const std::map<Instruction::InsName, bool>	_has_param;
};
#endif
