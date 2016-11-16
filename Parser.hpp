#ifndef PARSER
# define PARSER

# include "Token.hpp"
# include "Software.hpp"
# include "InstructionInfo.hpp"
# include <vector>
# include <map>

class Parser
{
	public:
		Parser(void);
		Parser(const Parser &obj);
		Parser &operator=(const Parser &p);
		virtual ~Parser(void);
		void	setTokenLst(const std::vector<Token> &lstToken);
		void	parse(void);
		static std::map<Token::Data, Instruction::InsName>	create_map(void);
	private:
		std::vector<Token>	_tokenLst;
		std::vector<Token>::iterator	_currentPos;
		Software			_prog;
		static const std::map<Token::Data, Instruction::InsName>	_tokenDataToIns;

		void				_processIns(Token const &tok);
};
#endif

