#include "InstructionInfo.hpp"

std::map<Instruction::InsName, bool> InstructionInfo::create_has_param()
{
	std::map<Instruction::InsName, bool>	map;
	map[Instruction::InsName::ADD] = false;
	map[Instruction::InsName::PUSH] = true;
	map[Instruction::InsName::DUMP] = false;
	map[Instruction::InsName::POP] = false;
	map[Instruction::InsName::ASSERT] = true;
	map[Instruction::InsName::SUB] = false;
	map[Instruction::InsName::MUL] = false;
	map[Instruction::InsName::DIV] = false;
	map[Instruction::InsName::MOD] = false;
	map[Instruction::InsName::PRINT] = false;
	map[Instruction::InsName::EXIT] = false;
	return map;
}

const std::map<Instruction::InsName, bool>	InstructionInfo::_has_param = InstructionInfo::create_has_param();

bool	InstructionInfo::hasParam(Instruction::InsName ins)
{
	try {
		return InstructionInfo::_has_param.at(ins);
	} catch (const std::out_of_range &e) {
		std::cerr << "hasParam -> Instruction not found" << std::endl;
	}
	return false;
}
