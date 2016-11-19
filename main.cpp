#include "Lexer.hpp"
#include "Parser.hpp"
#include "STDInReader.hpp"
#include "OperandFactory.hpp"
# include <fstream>

int main(int argc, char **argv)
{
	bool parserError, lexerError;
	STDInReader		reader;
	std::ifstream	*fs;

	if (argc < 2)
	{
		reader.read();
	} else {
		fs = new std::ifstream();
		fs->open(argv[1], std::fstream::in);
	}
	std::istream	*is = (argc < 2) ? reader.getIStream() : fs;

	Lexer	lexer(is);
	lexer.lex();
	lexerError = lexer.hasError();
	Parser	parser;
	parser.setTokenLst(lexer.getTokenLst());
	parser.parse();
	parserError = parser.hasError();
	if (parserError || lexerError)
	{
		delete fs;
		OperandFactory::deleteOp();
		std::cerr << "Error, exiting..." << std::endl;
		return 1;
	}
	parser.getSoftware().exec();
	OperandFactory::deleteOp();
	return 0;
}
