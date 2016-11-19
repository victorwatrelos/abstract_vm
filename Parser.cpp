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
	map[Token::Data::KEYWORD_FLOAT] = eOperandType::FLOAT;
	map[Token::Data::KEYWORD_DOUBLE] = eOperandType::DOUBLE;
	return map;
}

std::map<Token::Data, Instruction::InsName>	Parser::create_map(void)
{
	std::map<Token::Data, Instruction::InsName>	map;

	map[Token::Data::INS_ADD] = Instruction::InsName::ADD;
	map[Token::Data::INS_PUSH] = Instruction::InsName::PUSH;
	map[Token::Data::INS_DUMP] = Instruction::InsName::DUMP;
	map[Token::Data::INS_POP] = Instruction::InsName::POP;
	map[Token::Data::INS_ASSERT] = Instruction::InsName::ASSERT;
	map[Token::Data::INS_SUB] = Instruction::InsName::SUB;
	map[Token::Data::INS_MUL] = Instruction::InsName::MUL;
	map[Token::Data::INS_DIV] = Instruction::InsName::DIV;
	map[Token::Data::INS_MOD] = Instruction::InsName::MOD;
	map[Token::Data::INS_PRINT] = Instruction::InsName::PRINT;
	map[Token::Data::INS_EXIT] = Instruction::InsName::EXIT;
	return map;
}

const std::map<Token::Data, Instruction::InsName>	Parser::_tokenDataToIns = Parser::create_map();
const std::map<Token::Data, eOperandType>			Parser::_tokenDataToOp = Parser::create_map_op();

void		Parser::setTokenLst(const std::vector<Token> &lstToken)
{
	this->_tokenLst = lstToken;
}

IOperand const	*Parser::_getOpIns(int line)
{
	auto dist = std::distance(this->_currentPos, this->_tokenLst.end());
	Token					paramToken;
	Token					valueToken;

	if (dist < 5)
	{
		throw ParserError("Not enough param", line);
	}
	this->_currentPos++;
	paramToken = *this->_currentPos;
	if (paramToken.getType() != Token::Type::KEYWORD)
	{
		throw ParserError("Type name expected", line);
	}
	if ((*(this->_currentPos + 1)).getData() != Token::Data::OPEN_BRACKET
			|| (*(this->_currentPos + 3)).getData() != Token::Data::CLOSE_BRACKET)
	{
		throw ParserError("Bracket invalid", line);
	}
	valueToken = *(this->_currentPos + 2);
	if (valueToken.getType() != Token::Type::NUMBER)
	{
		throw ParserError("Parameter require a number", line);
	}
	this->_currentPos += 3;
	return this->_factory.createOperand(Parser::_tokenDataToOp.at(paramToken.getData()), valueToken.getNumber());
}

void		Parser::_processIns(Token const &tok)
{
	IOperand const			*op = nullptr;
	Instruction::InsName	insName = this->_tokenDataToIns.at(tok.getData());
	Instruction		ins;

	if (InstructionInfo::hasParam(insName))
	{
		op = this->_getOpIns(tok.getLine());
	}
	ins = Instruction(op, insName, tok.getLine());
	this->_prog.addIns(ins);
}

void		Parser::_processFirstToken(void)
{
	Token	token;

	token = *this->_currentPos;
	if (token.getType() == Token::Type::INSTRUCTION) {
		this->_processIns(token);
	} else {
		throw ParserError("Instruction expected", token.getLine());
	}
}

bool		Parser::hasError(void) const
{
	return this->_hasError;
}

void		Parser::parse(void)
{
	this->_currentPos = this->_tokenLst.begin();
	for (;this->_currentPos != this->_tokenLst.end(); this->_currentPos++)
	{
		try {
			this->_processFirstToken();
		} catch (ParserError &e) {
			if (e.getLine() > this->_lastLineError)
			{
				this->_lastLineError = e.getLine();
				std::cerr << e.what() << std::endl;
				this->_hasError = true;
			}
		} catch (AvmOverflowError &e) {
			std::cerr << e.what() << std::endl;
			this->_hasError = true;
		}
	}
}

Parser    &Parser::operator=(const Parser &p) {
	(void)p;
	return *this;
}

Software		&Parser::getSoftware(void)
{
	return this->_prog;
}
