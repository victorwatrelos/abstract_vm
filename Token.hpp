#ifndef TOKEN
# define TOKEN

# include <string>
# include <iostream>

class Token
{
	public:
		enum class Type {INSTRUCTION};
		Token(void);
		Token(const Token &obj);
		Token &operator=(const Token &p);
		virtual ~Token(void);
	private:
		int				_line;
		std::string		_filename;
		std::string		_data;
		Type			_type;
};
#endif

