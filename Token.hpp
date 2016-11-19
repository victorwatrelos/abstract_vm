#ifndef TOKEN
# define TOKEN

# include <string>
# include <iostream>

	class Token
	{
		public:
			enum class Type {INSTRUCTION, BRACKET, KEYWORD, NUMBER, EOL};
			enum class Data {OPEN_BRACKET,
							CLOSE_BRACKET,
							INS_ADD,
							INS_PUSH,
							INS_DUMP,
							INS_POP,
							INS_ASSERT,
							INS_SUB,
							INS_MUL,
							INS_DIV,
							INS_MOD,
							INS_PRINT,
							INS_EXIT,
							KEYWORD_INT32,
							KEYWORD_INT16,
							KEYWORD_INT8,
							KEYWORD_FLOAT,
							KEYWORD_DOUBLE,
							NONE};
			Token(void);
			Token(const Token &obj);
			Token(const Type &token_type, const Data &data, const std::string &filename, int line);
			Token(const std::string &number, const std::string &filename, int line);
			Token &operator=(const Token &p);
			virtual ~Token(void);
			Type				getType(void) const;
			Data				getData(void) const;
			std::string			getFilename(void) const;
			int					getLine(void) const;
			std::string const	&getNumber(void) const;
		private:
			Type			_type;
			Data			_data;
			std::string		_filename;
			int				_line;
			std::string		_number;
	};
#endif

