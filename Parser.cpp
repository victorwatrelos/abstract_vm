#include "Parser.hpp"

Parser::Parser(void) {
}

Parser::Parser(const Parser &obj) {
	*this = obj;
}

Parser::~Parser(void) {

}

std::map<Token::Data, eOperandType>	Parser::create_map_op(void)
{
	std::map<Token::Data, eOperandType>	map;

	map[Token::Data::KEYWORD_INT8] = eOperandType::INT_8;
	map[Token::Data::KEYWORD_INT16] = eOperandType::INT_16;
	map[Token::Data::KEYWORD_INT32] = eOperandType::INT_32;
	return map;
}

std::map<Token::Data, Instruction::InsName>	Parser::create_map(void)
{
	std::map<Token::Data, Instruction::InsName>	map;

	map[Token::Data::INS_ADD] = Instruction::InsName::ADD;
	map[Token::Data::INS_PUSH] = Instruction::InsName::PUSH;
	return map;
}

const std::map<Token::Data, Instruction::InsName>	Parser::_tokenDataToIns = Parser::create_map();
const std::map<Token::Data, eOperandType>			Parser::_tokenDataToOp = Parser::create_map_op();

void		Parser::setTokenLst(const std::vector<Token> &lstToken)
{
	this->_tokenLst = lstToken;
}

void		Parser::_processIns(Token const &tok)
{
	Instruction::InsName	insName = this->_tokenDataToIns.at(tok.getData());
	IOperand const			*op;
	Token					paramToken;
	Token					valueToken;

	if (!InstructionInfo::hasParam(insName))
	{
		std::cout << "No paran" << std::endl;
		return;
	}
	auto dist = std::distance(this->_currentPos, this->_tokenLst.end());
	if (dist < 5)
	{
		std::cerr << "Not enouth token" << std::endl;
		throw new std::exception;
	}
	this->_currentPos++;
	paramToken = *this->_currentPos;
	if (paramToken.getType() != Token::Type::KEYWORD)
	{
		std::cerr << "Not a number identifier" << std::endl;
		throw new std::exception;
	}
	if ((*(this->_currentPos + 1)).getData() != Token::Data::OPEN_BRACKET
			|| (*(this->_currentPos + 3)).getData() != Token::Data::CLOSE_BRACKET)
	{
		std::cerr << "Bad bracket" << std::endl;
		throw new std::exception;
	}
	valueToken = *(this->_currentPos + 2);
	if (valueToken.getType() != Token::Type::NUMBER)
	{
		std::cerr << "Not a number" << std::endl;
		throw new std::exception;
	}

	op = this->_factory.createOperand(Parser::_tokenDataToOp.at(paramToken.getData()), valueToken.getNumber());
	Instruction		ins = Instruction(op, insName);
	this->_prog.addIns(ins);
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

