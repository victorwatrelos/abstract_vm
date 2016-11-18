#ifndef LINEEXCEPTION_HPP
# define LINEEXCEPTION_HPP
class LineException
{
	public:
		LineException(void);
		LineException(int lineNb);
		LineException(const LineException &obj);
		LineException &operator=(const LineException &p);
		virtual ~LineException(void);
		int		getLine() const;
	private:
		int		_line;
};
#endif
