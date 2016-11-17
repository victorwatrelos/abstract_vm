#include "Lexer.hpp"
#include <fstream>
#include "Parser.hpp"

int main(int argc, char **argv)
{
	std::fstream	fs;
	if (argc < 2)
	{
		std::cerr << "Failure" << std::endl;
		return 1;
	}
	fs.open(argv[1], std::fstream::in);
	Lexer	lexer(&fs);
	lexer.lex();
	lexer.disp();
	Parser	parser;
	parser.setTokenLst(lexer.getTokenLst());
	parser.parse();
	return 0;
}
