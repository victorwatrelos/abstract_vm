#include "Lexer.hpp"

Lexer::Lexer(std::istream *ist)
	: _ist(ist)
{
}

std::map<std::string, Token::Data>			Lexer::_getLstInstruction(void)
{
	std::map<std::string, Token::Data>	map;
	map["add"] = Token::Data::INS_ADD;
	map["push"] = Token::Data::INS_PUSH;
	map["dump"] = Token::Data::INS_DUMP;
	map["pop"] = Token::Data::INS_POP;
	map["assert"] = Token::Data::INS_ASSERT;
	map["sub"] = Token::Data::INS_SUB;
	map["mul"] = Token::Data::INS_MUL;
	map["div"] = Token::Data::INS_DIV;
	map["mod"] = Token::Data::INS_MOD;
	map["print"] = Token::Data::INS_PRINT;
	map["exit"] = Token::Data::INS_EXIT;
	return map;
}

std::map<std::string, Token::Data>			Lexer::_getLstKeyword(void)
{
	std::map<std::string, Token::Data>	map;
	map["int8"] = Token::Data::KEYWORD_INT8;
	map["int16"] = Token::Data::KEYWORD_INT16;
	map["int32"] = Token::Data::KEYWORD_INT32;
	map["float"] = Token::Data::KEYWORD_FLOAT;
	map["double"] = Token::Data::KEYWORD_DOUBLE;
	return map;
}

const std::map<std::string, Token::Data>	Lexer::_lstInstruction = Lexer::_getLstInstruction();
const std::map<std::string, Token::Data>	Lexer::_lstKeyword = Lexer::_getLstKeyword();

Lexer::Lexer(const Lexer &obj) {
	*this = obj;
}

Lexer::~Lexer(void) {

}

std::istream	*Lexer::getIst() const
{
	return this->_ist;
}

void	Lexer::lex()
{
	this->_browseLine();
}

bool	Lexer::_isSeparator(const char &c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return true;
	return false;
}

bool	Lexer::hasError(void) const
{
	return this->_hasError;
}

bool	Lexer::_isKeyword(const std::string &elem)
{
	try {
		this->_lstKeyword.at(elem);
		return (true);
	} catch (const std::out_of_range &e) {
		return (false);
	}
}

void	Lexer::_addInsToken(const std::string &elem)
{
	Token::Data		ins;

	try {
		ins = this->_lstInstruction.at(elem);
		this->_lstToken.push_back(this->_getToken(Token::Type::INSTRUCTION, ins));
	} catch (const std::out_of_range &e) {
		throw LexerError("Symbole: " + elem + " not recognize", this->_currentLine);
	}
}

const std::vector<Token>		&Lexer::getTokenLst()
{
	return this->_lstToken;
}

bool	Lexer::isFloat(const std::string &str) {
	std::istringstream iss(str);
	float f;
	iss >> std::noskipws >> f;
	return iss.eof() && !iss.fail(); 
}

void	Lexer::_addNumberFloatToken(const std::string &elem)
{
	try {
		double res = std::stod(elem);
		this->_lstToken.push_back(Token(elem, this->_filename, this->_currentLine));
	} catch (const std::invalid_argument &e) {
		throw LexerError("Invalid number: " + elem, this->_currentLine);
	} catch (const std::out_of_range &e) {
		throw LexerError("Number overflow: " + elem, this->_currentLine);
	}
}

void	Lexer::_addNumberIntToken(const std::string &elem)
{
	int		res;

	try {
		this->_lstToken.push_back(Token(elem, this->_filename, this->_currentLine));
	} catch (const std::invalid_argument &e) {
		throw LexerError("Invalid number: " + elem, this->_currentLine);
	} catch (const std::out_of_range &e) {
		throw LexerError("Number overflow: " + elem, this->_currentLine);
	}
}

void	Lexer::_addKeywordToken(const std::string &elem)
{
	try {
		auto data = this->_lstKeyword.at(elem);
		this->_lstToken.push_back(this->_getToken(Token::Type::KEYWORD, data));
	} catch (const std::out_of_range &e) {
		throw LexerError("Keyword not recognise: " + elem, this->_currentLine);
	}
}

void	Lexer::_addToken(const std::string &elem)
{
	if (this->_firstOfLine)
	{
		this->_addInsToken(elem);
		this->_firstOfLine = false;
		return ;
	}
	if (Lexer::isDigits(elem))
	{
		this->_addNumberIntToken(elem);
		return ;
	}
	if (Lexer::isFloat(elem))
	{
		this->_addNumberFloatToken(elem);
		return ;
	}
	if (this->_isKeyword(elem))
	{
		this->_addKeywordToken(elem);
		return ;
	}
	
}

bool Lexer::isDigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

Token	Lexer::_getToken(const Token::Type &type, const Token::Data &data) const
{
	return Token(type, data, this->_filename, this->_currentLine);
}

void	Lexer::_endOfToken(void)
{
	if (this->_buffer.length() > 0)
	{
		this->_addToken(this->_buffer);
		this->_buffer = "";
	}
}

bool	Lexer::_isBracket(const char &c)
{
	if (c == '(' || c == ')')
		return true;
	return false;
}

void	Lexer::_addBracketToken(const char &c)
{
	if (c == '(') {
		this->_lstToken.push_back(
				this->_getToken(Token::Type::BRACKET, Token::Data::OPEN_BRACKET)
				);
	} else if (c == ')') {
		this->_lstToken.push_back(
				this->_getToken(Token::Type::BRACKET, Token::Data::CLOSE_BRACKET)
				);
	}
}

void	Lexer::_processLine(const std::string &line)
{
	try {
		this->_firstOfLine = true;
		for (auto i : line)
		{
				if (i == ';')
				{
					this->_endOfToken();
					return ;
				}
				if (Lexer::_isSeparator(i)) {
					this->_endOfToken();
				} else if (Lexer::_isBracket(i)) {
					this->_endOfToken();
					this->_addBracketToken(i);
					this->_endOfToken();
				} else {
					this->_buffer += i;
				}
		}
		this->_endOfToken();
	} catch (LexerError &e) {
		std::cerr << e.what() << std::endl;
		this->_hasError = true;
		this->_buffer = "";
	}
}

void	Lexer::_browseLine() {
	std::string		line;

	this->_currentLine = 1;
	while (std::getline(*this->_ist, line))
	{
		this->_processLine(line);
		this->_currentLine++;
	}
}

Lexer    &Lexer::operator=(const Lexer &p) {
	this->_ist = p.getIst();
	return *this;
}

