#include "Lexer.hpp"
#include <fstream>
#include "Parser.hpp"

int main(int argc, char **argv)
{
	bool parserError, lexerError;

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
	lexerError = lexer.hasError();
	Parser	parser;
	parser.setTokenLst(lexer.getTokenLst());
	parser.parse();
	parserError = parser.hasError();
	if (parserError || lexerError)
	{
		std::cerr << "Error, exiting..." << std::endl;
		return 1;
	}
	parser.getSoftware().exec();
	return 0;
}
