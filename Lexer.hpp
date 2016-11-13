#ifndef LEXER
# define LEXER

# include "Token.hpp"
# include <string>
# include <iostream>
# include <vector>

class Lexer
{
	public:
		Lexer(void);
		Lexer(std::istream *ist);
		Lexer(const Lexer &obj);
		Lexer &operator=(const Lexer &p);
		virtual ~Lexer(void);
		std::istream	*getIst() const;
		void			lex();
	private:
		void				_browseLine(void);
		void				_processLine(const std::string &line);
		static bool			_isSeparator(const char &c);
		static bool			_isBracket(const char &c);
		Token				_getToken(const Token::Type &type, const Token::Data &data) const;
		void				_addToken(std::string elem);
		void				_addBracketToken(const char &c);
		void				_endOfToken(void);
		std::istream		*_ist = nullptr;
		std::vector<Token>	_lstToken;
		int					_currentLine = -1;
		std::string			_buffer = "";
		std::string			_filename = "STDIN";
};
#endif

