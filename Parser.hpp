#ifndef PARSER
# define PARSER

# include "Token.hpp"
# include <vector>

class Parser
{
	public:
		Parser(void);
		Parser(const Parser &obj);
		Parser &operator=(const Parser &p);
		virtual ~Parser(void);
		void	setTokenLst(const std::vector<Token> &lstToken);
	private:
		std::vector<Token>	_tokenLst;
};
#endif

