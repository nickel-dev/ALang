#include <iostream>
#include <vector>
#include <string>

#include "Lexer.hpp"

int main(int argc, char *argv[])
{
	std::string code = "main : i32 = 0;";

	CLexer *lexer = new CLexer(code);

	for (CToken token : lexer->tokens)
	{
		std::cout << "['" << token.data << "' : " << token.type << "]";
	}
	std::cout << std::endl;

	delete lexer;

	return 0;
}