#ifndef TOKEN
# define TOKEN

# include <string>
# include <iostream>

class Token
{
	public:
		enum class Type {INSTRUCTION, BRACKET};
		enum class Data {OPEN_BRACKET, CLOSE_BRACKET, INSTRUCTION};
		Token(void);
		Token(const Token &obj);
		Token(const Type &token_type, const Data &data, const std::string &filename, int line);
		Token &operator=(const Token &p);
		virtual ~Token(void);
	private:
		Type			_type;
		Data			_data;
		std::string		_filename;
		int				_line;
};
#endif

