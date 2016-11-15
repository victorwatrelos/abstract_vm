#ifndef LEXER
# define LEXER

# include "Token.hpp"
# include <string>
# include <iostream>
# include <vector>
# include <map>
# include <sstream>

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
		void			disp();
		const std::vector<Token>	&getTokenLst();
		static bool 			isDigits(const std::string &str);
		static bool				isFloat(const std::string &str);
	private:
		void				_browseLine(void);
		void				_processLine(const std::string &line);
		static bool			_isSeparator(const char &c);
		static bool			_isBracket(const char &c);
		Token				_getToken(const Token::Type &type, const Token::Data &data) const;
		void				_addToken(const std::string &elem);
		void				_addBracketToken(const char &c);
		void				_endOfToken(void);
		void				_addInsToken(const std::string &elem);
		bool				_isKeyword(const std::string &elem);
		void				_addNumberIntToken(const std::string &elem);
		void				_addNumberFloatToken(const std::string &elem);
		void				_addKeywordToken(const std::string &elem);
		std::istream		*_ist = nullptr;
		std::vector<Token>	_lstToken;
		int					_currentLine = -1;
		std::string			_buffer = "";
		std::string			_filename = "STDIN";
		bool				_firstOfLine;
		std::map<std::string, Token::Data>	_lstInstruction;
		std::map<std::string, Token::Data>	_lstKeyword;
		std::vector<std::string>	_errors;
};
#endif

