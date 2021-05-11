#include "ExpressionParser.h"
#include "TestHelper.h"
#include <iostream>
#include <vector>

int main()
{
	//auto testHelper = TestHelper();
	//testHelper.runSpeedTests();
	//std::string in{};
	//std::getline(std::cin, in);
	//auto queue = ExpressionParser::parseExpression(in);
	//std::cout << ExpressionParser::toString(queue) << '\n';
	//auto result = ExpressionParser::calculateExpression(queue);
	//std::cout << "Result: " << result << '\n';


	std::string in{};
	std::getline(std::cin, in);
	auto queue = ExpressionParser::parseExpression(in);
	std::cout << ExpressionParser::toString(queue) << '\n';
}