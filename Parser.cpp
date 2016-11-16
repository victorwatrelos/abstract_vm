#include "Parser.hpp"

Parser::Parser(void) {
}

Parser::Parser(const Parser &obj) {
	*this = obj;
}

Parser::~Parser(void) {

}

std::map<Token::Data, Instruction::InsName>	Parser::create_map(void)
{
	std::map<Token::Data, Instruction::InsName>	map;

	map[Token::Data::INS_ADD] = Instruction::InsName::ADD;
	map[Token::Data::INS_PUSH] = Instruction::InsName::PUSH;
	return map;
}

const std::map<Token::Data, Instruction::InsName>	Parser::_tokenDataToIns = Parser::create_map();

void		Parser::setTokenLst(const std::vector<Token> &lstToken)
{
	this->_tokenLst = lstToken;
}

void		Parser::_processIns(Token const &tok)
{
	Instruction		ins;
	Instruction::InsName	insName = this->_tokenDataToIns.at(tok.getData());

	if (!InstructionInfo::has_param(insName))
	{
		//this->_program.addIns(Instruction(token //TODO THERE
	}
}

void		Parser::parse(void)
{
	std::cout << "Start parsing" << std::endl;
	Token	token;
	this->_currentPos = this->_tokenLst.begin();
	for (;this->_currentPos != this->_tokenLst.end(); this->_currentPos++)
	{
		token = *this->_currentPos;
		if (token.getType() == Token::Type::INSTRUCTION)
		{
			this->_processIns(token);
		}
	}
	this->_prog.disp();
}

Parser    &Parser::operator=(const Parser &p) {
	(void)p;
	return *this;
}

