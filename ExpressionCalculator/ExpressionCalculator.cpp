#include "ExpressionParser.h"
#include <iostream>

int main()
{
	std::string in{};
	std::getline(std::cin, in);
	auto parsedString = ExpressionParser::parseExpression(in);
	std::cout << parsedString << '\n';
}