#ifndef TOKEN
# define TOKEN

# include <string>
# include <iostream>

	class Token
	{
		public:
			enum class Type {INSTRUCTION, BRACKET, KEYWORD, NUMBER_INT, NUMBER_FLOAT};
			enum class Data {OPEN_BRACKET, CLOSE_BRACKET, INS_ADD, KEYWORD_INT32, KEYWORD_INT16, KEYWORD_INT8};
			Token(void);
			Token(const Token &obj);
			Token(const Type &token_type, const Data &data, const std::string &filename, int line);
			Token(const int number, const std::string &filename, int line);
			Token(const double number, const std::string &filename, int line);
			Token &operator=(const Token &p);
			virtual ~Token(void);
			void	disp();
			static std::string		getTypeStr(const Type &type);
			static std::string		getDataStr(const Data &data);
			Type				getType(void) const;
			Data				getData(void) const;
			std::string			getFilename(void) const;
			int					getLine(void) const;
		private:
			Type			_type;
			Data			_data;
			std::string		_filename;
			int				_line;
			int				_numberInt;
			double			_numberFloat;
	};
#endif

